//
// Created by mathis on 02/06/2020.
//
#include "WaterRenderer.hpp"

WaterRenderer::WaterRenderer(StaticShader *shader) : EntityRenderer(shader) {
    m_reflectionFbo =
        std::make_unique<FBO>(1280, 720, 1, FBO::Attachments{FBO::Attachments::TEXTURE, 1, FBO::Attachments::BUFFER});
    m_refractionFbo =
        std::make_unique<FBO>(1280, 720, 1, FBO::Attachments{FBO::Attachments::TEXTURE, 1, FBO::Attachments::TEXTURE});
}

WaterRenderer::~WaterRenderer() {
    m_reflectionFbo.reset();
    m_refractionFbo.reset();
}

void WaterRenderer::render(std::vector<Water> &waters, const LightCollection &lights, double deltatime) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    setLights(lights);
    for (auto &water : waters) {
        m_shaderProgram->setMat4("model", water.model());
        water.material().texture("reflectionTex").id() = m_reflectionFbo->textures()[0];
        water.material().texture("refractionTex").id() = m_refractionFbo->textures()[0];
        water.material().texture("refractionDepth").id() = m_refractionFbo->textures()[1];
        water.move(deltatime);
        m_shaderProgram->setMaterial(water.material(), "waterMat");
        m_shaderProgram->setInt("entityType", Renderable::Type::WATER);
        water.prepare();
        water.render(GL_TRIANGLES);
        water.unbind();
    }
    m_shaderProgram->clearLights();
    glDisable(GL_BLEND);
}
