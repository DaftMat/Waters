//
// Created by mathis on 06/06/2020.
//
#include "SkyShader.hpp"

void SkyShader::loadCubeMap(const Texture &cubeMap) {
    setInt(cubeMap.name(), 0);
}

void SkyShader::loadMatrices(const glm::mat4 &proj, const glm::mat4 &view) {
    setMat4("projection", proj);
    setMat4("view", view);
}
