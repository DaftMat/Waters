#version 450
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTex;

out vec3 toCamera;
out float visibility;
out vec4 clipSpace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec4 clipPlane;

uniform float fog_density;
uniform float fog_gradient;

void main() {
    vec4 worldPos = model * vec4(aPos, 1.0);
    gl_ClipDistance[0] = dot(worldPos, clipPlane);

    fragPos = worldPos.xyz;
    fragNormal = mat3(transpose(inverse(model))) * aNormal;
    fragTex = aTex;

    vec4 positionRelativeToCam = view * vec4(fragPos, 1.0);
    clipSpace = projection * positionRelativeToCam;
    gl_Position = clipSpace;
    toCamera = (inverse(view) * vec4(vec3(0.0), 1.0)).xyz - fragPos.xyz;

    float dist = length(positionRelativeToCam.xyz);
    visibility = exp(-pow(dist * fog_density, fog_gradient));
    visibility = clamp(visibility, 0.0, 1.0);
}