//
// Created by mathis on 01/06/2020.
//
#include "StaticShader.hpp"

#include <Minimal-Engine/Material/Material.hpp>

void StaticShader::setMaterial(const Material &material, const std::string &name) const {
    for (int i = 0; i < material.textures().size(); ++i) {
        setInt(name + "." + material.textures()[i].name(), i);
    }
    for (const auto &setting : material.settings()) {
        switch (setting.type) {
            case Material::Setting::Type::VECTOR:
                setVec3(name + "." + setting.name, setting.data.vectorData);
                break;
            case Material::Setting::Type::SCALAR:
                setFloat(name + "." + setting.name, setting.data.scalarData);
                break;
            case Material::Setting::Type::BOOL:
                setBool(name + "." + setting.name, setting.data.boolData);
                break;
            case Material::Setting::Type::INT:
                setInt(name + "." + setting.name, setting.data.intData);
                break;
        }
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
