#version 450
layout (location = 0) out vec4 fragColor;

in vec3 texCoords;

uniform samplerCube cubeMap;

void main() {
    fragColor = texture(cubeMap, texCoords);
}
