//
// Created by mathis on 06/06/2020.
//
#include "ObjectRenderer.hpp"

void ObjectRenderer::render(const std::vector<Object> &objects, const LightCollection &lights) {
    setLights(lights);
    for (const auto &o : objects) {
        render(o);
    }
    clearLights();
}

void ObjectRenderer::render(const Object &object) {
    m_shaderProgram->setMat4("model", object.model());
    m_shaderProgram->setMaterial(object.material(), "objectMat");
    m_shaderProgram->setInt("entityType", Renderable::Type::OBJECT);
    object.prepare();
    object.render(GL_TRIANGLES);
    object.unbind();
}
