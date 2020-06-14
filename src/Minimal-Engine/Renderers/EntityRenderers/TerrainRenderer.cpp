//
// Created by mathis on 13/05/2020.
//

#include "TerrainRenderer.hpp"

#include <Minimal-Engine/Renderables/StaticObjects/TerrainGrid.hpp>

void TerrainRenderer::render(const TerrainGrid &terrains, const LightCollection &lights) {
    setLights(lights);
    for (const auto &t : terrains) {
        m_shaderProgram->setMat4("model", t.second.model());
        m_shaderProgram->setMaterial(t.second.material(), "terrainMat");
        m_shaderProgram->setInt("entityType", Renderable::Type::TERRAIN);
        t.second.prepare();
        t.second.render(GL_TRIANGLES);
        t.second.unbind();
    }
    m_shaderProgram->clearLights();
}
