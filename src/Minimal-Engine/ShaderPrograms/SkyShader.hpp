//
// Created by mathis on 06/06/2020.
//
#pragma once

#include <Minimal-Engine/Material/Texture.hpp>

#include "ShaderProgram.hpp"

class SkyShader : public ShaderProgram {
   public:
    SkyShader(const char *vertPath, const char *fragPath) : ShaderProgram(vertPath, fragPath) {}

    void loadCubeMap(const Texture &cubeMap);

    void loadMatrices(const glm::mat4 &proj, const glm::mat4 &view);
};
