//
// Created by mathis on 06/06/2020.
//
#pragma once


#include <memory>
#include <Minimal-Engine/ShaderPrograms/SkyShader.hpp>
#include <Minimal-Engine/Geometry/Mesh.hpp>
#include <Minimal-Engine/Renderables/Cameras/Camera.hpp>
#include <Minimal-Engine/Renderables/Skyboxes/Skybox.hpp>

class SkyRenderer {
public:
    explicit SkyRenderer(const std::string &skyDir, float size);

    void prepare() const;

    void render();

    void unbind() const;

    void loadMatrices(const glm::mat4& view, const glm::mat4& proj);

    [[nodiscard]] const Skybox &skybox() const { return m_skybox; }

    Skybox &skybox() { return m_skybox; }

    void rotate(float deltatime);

private:
    Skybox m_skybox;

    std::unique_ptr<SkyShader> m_shader{nullptr};
    float m_rotation{0.f};
};
