//
// Created by mathis on 01/06/2020.
//
#include <Core/Log.hpp>
#include "Renderer.hpp"

Renderer::Renderer(int width, int height, float near, float far, float fogDensity, float fogGradient, const glm::vec3 &skyColor) :
m_width {width}, m_height {height}, m_near {near}, m_far {far}, m_fogDensity {fogDensity}, m_fogGradient {fogGradient}, m_skyColor{skyColor} {
    initGL();
    m_terrainRenderer.setShader("shaders/blinnphong.vert.glsl", "shaders/blinnphong.frag.glsl");

    glViewport(0, 0, width, height);
    glEnable( GL_MULTISAMPLE );
    glDepthFunc( GL_LESS );
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
}

void Renderer::prepare() const {
    glEnable(GL_DEPTH_TEST);
    glClearColor(m_skyColor.r, m_skyColor.g, m_skyColor.b, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::render(const LightCollection &lights, const Camera &camera) {
    auto view = camera.getViewMatrix();
    auto proj = glm::perspective(camera.getFov(), float(m_width)/float(m_height), m_near, m_far);

    m_terrainRenderer.prepare();
    m_terrainRenderer.loadMatrices(view, proj);
    m_terrainRenderer.loadFog(m_fogDensity, m_fogGradient);
    m_terrainRenderer.loadSky(m_skyColor);
    m_terrainRenderer.render(m_terrains, lights);
    m_terrainRenderer.unbind();
}

void Renderer::resize(int width, int height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void Renderer::initGL() {
    if (!gladLoadGL()) {
        ENGINE_ERROR("Failed to load OpenGL.");
        exit(-1);
    }
}
