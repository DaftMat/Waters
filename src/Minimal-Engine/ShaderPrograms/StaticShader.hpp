//
// Created by mathis on 01/06/2020.
//
#pragma once
#include <API.hpp>
#include <Minimal-Engine/Material/Material.hpp>
#include <Minimal-Engine/Renderables/Lights/PointLight.hpp>
#include <Minimal-Engine/Renderables/Lights/DirectLight.hpp>
#include "ShaderProgram.hpp"

class ENGINE_API StaticShader : public ShaderProgram {
public:
    StaticShader(const char *vertexPath, const char *fragmentPath) : ShaderProgram(vertexPath, fragmentPath) {}

    void setMaterial(const Material &material, const std::string &name) const;

    void addLight(const PointLight &light);

    void addLight(const DirectLight &light);

    void clearLights();

private:
    GLuint m_numPointLights {0};
    GLuint m_numDirectLights {0};
};
