//
// Created by mathis on 09/05/2020.
//

#include "Object.hpp"

Object::Object(Mesh mesh, const glm::vec3 &pos, const glm::vec3 &rot, const glm::vec3 &scale)
    : m_position{pos}, m_rotation{rot}, m_scale{scale} {
    m_mesh = std::move(mesh);
    m_material.addSetting("hasAlbedoTex", false);
    m_material.addSetting("hasSpecularTex", false);
    m_material.addSetting("albedo", glm::vec3{0.5f});
    m_material.addSetting("specular", glm::vec3{1.f});
    m_material.addSetting("reflectivity", 0.5f);
    m_material.addSetting("shininess", 1.f);
    m_material.addSetting("isTransparent", false);
    m_material.addSetting("useFakeLighting", false);
}

glm::mat4 Object::rotation() const {
    glm::mat4 rx, ry, rz;
    rx = glm::rotate(glm::mat4{1.f}, glm::radians(m_rotation.x), {1.f, 0.f, 0.f});
    ry = glm::rotate(glm::mat4{1.f}, glm::radians(m_rotation.y), {0.f, 1.f, 0.f});
    rz = glm::rotate(glm::mat4{1.f}, glm::radians(m_rotation.z), {0.f, 0.f, 1.f});
    return rx * ry * rz;
}

void Object::addAlbedoTexture(const std::string &texPath) {
    m_material.addTexture(Texture("albedoTex", texPath));
    m_material.setSetting("hasAlbedoTex", true);
}

void Object::addSpecularTexture(const std::string &texPath) {
    m_material.addTexture(Texture("specularTex", texPath));
    m_material.setSetting("hasSpecularTex", true);
}
