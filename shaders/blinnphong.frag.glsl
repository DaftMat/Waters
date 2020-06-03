#version 450
layout (location = 0) out vec4 fragColor;

const int MAX_LIGHTS = 32;

//types of entity
const int OBJECT_T  = 0;
const int TERRAIN_T = 1;
const int WATER_T   = 2;

struct ObjectMaterial {
// textures
    sampler2D albedoTex;
    sampler2D specularTex;
    bool hasAlbedoTex;
    bool hasSpecularTex;
// colors
    vec3 albedo;
    vec3 specular;
// other data
    float reflectivity;
    float shininess;
    bool isTransparent;
    bool useFakeLighting;
};

struct TerrainMaterial {
    float reflectivity;
    float shininess;
    float tileFactor;
};

struct WaterMaterial {
    sampler2D dudvMap;
    sampler2D normalMap;
    sampler2D reflectionTex;
    sampler2D refractionTex;
    sampler2D refractionDepth;
    float near;
    float far;
    float offset;
    float distortionForce;
    float reflectivity;
    float shininess;
    float tileFactor;
};

struct PointLight {
    vec3 position;
    float intensity;
    vec3 color;
};

struct DirectLight {
    vec3 direction;
    vec3 color;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float innerCutoff;
    float outerCutoff;
    float intensity;
    vec3 color;
};

struct GenericMaterial {
    float shininess;
    float reflectivity;
    vec4 albedo;
    vec4 specular;
};


in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTex;

in vec3 toCamera;
in float visibility;
in vec4 clipSpace;

uniform PointLight pointLights[MAX_LIGHTS];
uniform DirectLight directLights[MAX_LIGHTS];
uniform SpotLight spotLights[MAX_LIGHTS];

uniform int numPointLights;
uniform int numDirectLights;
uniform int numSpotLights;

uniform int entityType;
uniform ObjectMaterial objectMat;
uniform TerrainMaterial terrainMat;
uniform WaterMaterial waterMat;
uniform vec3 skyColor;

vec3 shade(PointLight light, vec3 normal, GenericMaterial mat);
vec3 shade(DirectLight light, vec3 normal, GenericMaterial mat);
vec3 shade(SpotLight light, vec3 normal, GenericMaterial mat);

GenericMaterial getGenericMat(ObjectMaterial mat);
GenericMaterial getGenericMat(TerrainMaterial mat);
GenericMaterial getGenericMat(WaterMaterial mat);

//helpers
float distance(float near, float far, float depth);

vec3 normal;

void main() {
    normal = normalize(fragNormal);
    vec3 resultColor = vec3(0.0);

    GenericMaterial mat;
    if (entityType == OBJECT_T) {
        if (objectMat.useFakeLighting)
            normal = vec3(0.0, 1.0, 0.0);
        mat = getGenericMat(objectMat);
    } else if (entityType == TERRAIN_T) {
        mat = getGenericMat(terrainMat);
    } else if (entityType == WATER_T) {
        mat = getGenericMat(waterMat);
        resultColor = mat.albedo.rgb;
        mat.albedo = vec4(vec3(0.0), mat.albedo.a); // add only specular color with shade functions to water.
    }

    for (int i = 0 ; i < numPointLights ; ++i) {
        resultColor += shade(pointLights[i], normal, mat);
    }

    for (int i = 0 ; i < numDirectLights ; ++i) {
        resultColor += shade(directLights[i], normal, mat);
    }

    for (int i = 0 ; i < numSpotLights ; ++i) {
        resultColor += shade(spotLights[i], normal, mat);
    }

    // ambient + gamma
    vec3 color = resultColor;
    if (entityType != WATER_T) {
        vec3 ambient = vec3(0.03) * mat.albedo.rgb;
        color += ambient;
        color = color / (color + vec3(1.0));
        color = pow(color, vec3(1.0/2.2));
    }
    fragColor = vec4(color, mat.albedo.a);
    // fog
    fragColor = mix(vec4(skyColor, 1.0), fragColor, visibility);
}

vec3 shade(PointLight light, vec3 normal, GenericMaterial mat) {
    vec3 lightDir = light.position - fragPos;
    float distance = length(lightDir);
    lightDir = normalize(lightDir);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 halfwayDir = normalize(lightDir + toCamera);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), mat.shininess);
    float attenuation = light.intensity / (distance * distance);
    vec3 diffuse = light.color * diff * mat.albedo.rgb * attenuation;
    vec3 specular = light.color * spec * mat.specular.rgb * attenuation * mat.reflectivity;
    return diffuse + specular;
}

vec3 shade(DirectLight light, vec3 normal, GenericMaterial mat){
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 halfwayDir = normalize(lightDir + toCamera);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), mat.shininess);
    vec3 diffuse = light.color * diff * mat.albedo.rgb;
    vec3 specular = light.color * spec * mat.specular.rgb * mat.reflectivity;
    return diffuse + specular;
}

vec3 shade(SpotLight light, vec3 normal, GenericMaterial mat) {
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 halfwayDir = normalize(lightDir + toCamera);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), mat.shininess);
    float distance = length(light.position - fragPos);
    float attenuation = light.intensity / (distance * distance);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.innerCutoff - light.outerCutoff;
    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);;
    vec3 diffuse = light.color * diff * mat.albedo.rgb;
    vec3 specular = light.color * spec * mat.specular.rgb * mat.reflectivity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return diffuse + specular;
}

GenericMaterial getGenericMat(ObjectMaterial mat) {
    GenericMaterial ret;
    ret.shininess = mat.shininess;
    ret.reflectivity = mat.reflectivity;
    //albedo
    ret.albedo = vec4(mat.albedo, 1.0);
    if (mat.hasAlbedoTex)
        ret.albedo = texture(mat.albedoTex, fragTex);
    if (mat.isTransparent && ret.albedo.a < 0.1)
        discard;
    //specular
    ret.specular = vec4(mat.specular, 1.0);
    if (mat.hasSpecularTex)
        ret.specular = texture(mat.specularTex, fragTex);

    return ret;
}

GenericMaterial getGenericMat(TerrainMaterial mat) {
    GenericMaterial ret;
    ret.shininess = mat.shininess;
    ret.reflectivity = mat.reflectivity;
    ret.specular = vec4(vec3(0.8), 1.0);
    //albedo

    //vec2 tiledCoords = fragTex * mat.tileFactor;
    ret.albedo = vec4(vec3(0.3), 1.0);
    /**
    vec4 blend = texture(mat.blendMap, fragTex);
    float blackTexAmount = 1.0 - (blend.r + blend.g + blend.b);
    vec4 black = texture(mat.blackTex, tiledCoords) * blackTexAmount;
    vec4 red = texture(mat.redTex, tiledCoords) * blend.r;
    vec4 green = texture(mat.greenTex, tiledCoords) * blend.g;
    vec4 blue = texture(mat.blueTex, tiledCoords) * blend.b;
    ret.albedo = black + red + green + blue;
    **/

    return ret;
}

GenericMaterial getGenericMat(WaterMaterial mat) {
    GenericMaterial ret;
    ret.shininess = mat.shininess;
    ret.reflectivity = mat.reflectivity;
    ret.specular = vec4(1.0);

    vec2 ndc = (clipSpace.xy / clipSpace.w) * 0.5 + 0.5;
    vec2 refracCoords = ndc;
    vec2 reflecCoords = vec2(ndc.x, -ndc.y);

    float depth = texture(mat.refractionDepth, refracCoords).r;
    float floorDist = distance(mat.near, mat.far, depth);
    depth = gl_FragCoord.z;
    float waterDist = distance(mat.near, mat.far, depth);
    float waterDepth = floorDist - waterDist;

    vec2 tiledCoords = mat.tileFactor * fragTex;
    vec2 distordedCoords = texture(mat.dudvMap, vec2(tiledCoords.x + mat.offset, tiledCoords.y)).rg * 0.1;
    distordedCoords = tiledCoords + vec2(distordedCoords.x, distordedCoords.y + mat.offset);
    vec2 totalDistortion = (texture(mat.dudvMap, distordedCoords).rg * 2.0 - 1.0) * mat.distortionForce * clamp(waterDepth/20.0, 0.0, 1.0);

    vec4 normalColor = texture(mat.normalMap, distordedCoords);
    normal = normalize(vec3(normalColor.r * 2.0 - 1.0, normalColor.b * 1.0, normalColor.g * 2.0 - 1.0));

    reflecCoords += totalDistortion;
    reflecCoords.x = clamp(reflecCoords.x, 0.001, 0.999);
    reflecCoords.y = clamp(reflecCoords.y, -0.999, -0.001);

    refracCoords += totalDistortion;
    refracCoords = clamp(refracCoords, 0.001, 0.999);

    vec4 reflection = texture(mat.reflectionTex, reflecCoords);
    vec4 refraction = texture(mat.refractionTex, refracCoords);

    float coef = pow(dot(normalize(toCamera), normal), mat.reflectivity);
    coef = clamp(coef, 0.0, 1.0);

    ret.albedo = mix(reflection, refraction, coef);
    ret.albedo.a = clamp(waterDepth/5.0, 0.0, 1.0);
    return ret;
}

float distance(float near, float far, float depth) {
    return 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
}