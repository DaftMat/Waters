//
// Created by mathis on 01/06/2020.
//
#include "StaticShader.hpp"

#include <Minimal-Engine/Material/Material.hpp>

void StaticShader::setMaterial(const Material &material, const std::string &name) const {
    /// Textures
    for (int i = 0; i < material.textures().size(); ++i) {
        setInt(name + "." + material.textures()[i].name(), i);
    }
    /// Int settings
    for (auto &setting : material.settings<int>()) {
        setInt(name + "." + setting.name, setting.data);
    }
    /// Bool settings
    for (auto &setting : material.settings<bool>()) {
        setBool(name + "." + setting.name, setting.data);
    }
    /// Float settings
    for (auto &setting : material.settings<float>()) {
        setFloat(name + "." + setting.name, setting.data);
    }
    /// Vec2 settings
    for (auto &setting : material.settings<glm::vec2>()) {
        setVec2(name + "." + setting.name, setting.data);
    }
    /// Vec3 settings
    for (auto &setting : material.settings<glm::vec3>()) {
        setVec3(name + "." + setting.name, setting.data);
    }
    /// Vec4 settings
    for (auto &setting : material.settings<glm::vec4>()) {
        setVec4(name + "." + setting.name, setting.data);
    }
    /// Mat2 settings
    for (auto &setting : material.settings<glm::mat2>()) {
        setMat2(name + "." + setting.name, setting.data);
    }
    /// Mat3 settings
    for (auto &setting : material.settings<glm::mat3>()) {
        setMat3(name + "." + setting.name, setting.data);
    }
    /// Mat4 settings
    for (auto &setting : material.settings<glm::mat4>()) {
        setMat4(name + "." + setting.name, setting.data);
    }
}

void StaticShader::addLight(const PointLight &light) {
    std::string index = std::to_string(m_numPointLights++);
    setVec3("pointLights[" + index + "].position", light.position());
    setVec3("pointLights[" + index + "].color", light.color());
    setFloat("pointLights[" + index + "].intensity", light.intensity());
    setInt("numPointLights", m_numPointLights);
}

void StaticShader::addLight(const DirectLight &light) {
    std::string index = std::to_string(m_numDirectLights++);
    setVec3("directLights[" + index + "].direction", light.direction());
    setVec3("directLights[" + index + "].color", light.color());
    setInt("numDirectLights", m_numDirectLights);
}

void StaticShader::clearLights() {
    m_numPointLights = 0;
    m_numDirectLights = 0;
    setInt("numPointLights", m_numPointLights);
    setInt("numDirectLights", m_numDirectLights);
}

void StaticShader::setSkybox(const Skybox &skybox) const { setMaterial(skybox.material(), "skybox"); }
