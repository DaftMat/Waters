//
// Created by mathis on 06/06/2020.
//
#include "SkyRenderer.hpp"

#include <Minimal-Engine/Geometry/Primitives.hpp>

SkyRenderer::SkyRenderer(const std::string &skyDir, float size) : m_skybox{skyDir, size} {
    m_shader = std::make_unique<SkyShader>("shaders/sky.vert.glsl", "shaders/sky.frag.glsl");
}

void SkyRenderer::prepare() const {
    glDepthMask(GL_FALSE);
    m_shader->use();
}

void SkyRenderer::render() {
    m_shader->loadCubeMap(m_skybox.material().texture("cubeMap"));
    m_skybox.prepare();
    m_skybox.render(GL_TRIANGLES);
    m_skybox.unbind();
}

void SkyRenderer::unbind() const {
    m_shader->stop();
    glDepthMask(GL_TRUE);
}

void SkyRenderer::rotate(float deltatime) { m_rotation += m_skybox.speed() * deltatime; }

void SkyRenderer::loadMatrices(const glm::mat4 &view, const glm::mat4 &proj) {
    glm::mat4 resView = view;
    resView[3][0] = 0.f;
    resView[3][1] = 0.f;
    resView[3][2] = 0.f;
    resView = glm::rotate(resView, m_rotation, glm::vec3{0.f, 1.f, 0.f});
    m_shader->loadMatrices(proj, resView);
}
