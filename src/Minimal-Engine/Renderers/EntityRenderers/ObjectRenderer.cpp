//
// Created by mathis on 06/06/2020.
//
#include "ObjectRenderer.hpp"

void ObjectRenderer::render(const std::vector<Object> &objects, const LightCollection &lights) {
    setLights(lights);
    for (const auto &o : objects) {
        m_shaderProgram->setMat4("model", o.model());
        m_shaderProgram->setMaterial(o.material(), "objectMat");
        m_shaderProgram->setInt("entityType", Renderable::Type::OBJECT);
        o.prepare();
        o.render(GL_TRIANGLES);
        o.unbind();
    }
    m_shaderProgram->clearLights();
}
