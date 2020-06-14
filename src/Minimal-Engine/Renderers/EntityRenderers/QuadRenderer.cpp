//
// Created by mathis on 18/05/2020.
//

#include "QuadRenderer.hpp"

QuadRenderer::QuadRenderer() {
    m_shader = std::make_unique<QuadShader>("shaders/quad.vert.glsl", "shaders/quad.frag.glsl");
}

void QuadRenderer::render() const {
    m_shader->use();
    for (const auto &quad : m_quads) {
        quad.prepare();
        m_shader->setTexture();
        quad.render(GL_TRIANGLES);
        quad.unbind();
    }
    m_shader->stop();
}

void QuadRenderer::prepare() const {
    glDisable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}