//
// Created by mathis on 13/05/2020.
//

#ifndef DAFT_GAMEENGINE_TERRAINRENDERER_HPP
#define DAFT_GAMEENGINE_TERRAINRENDERER_HPP

#include <Minimal-Engine/Renderables/Lights/LightCollection.hpp>
#include <Minimal-Engine/Renderables/StaticObjects/Terrain.hpp>

#include "EntityRenderer.hpp"

/** Renderer specially for Terrains
 *
 */
class TerrainRenderer : public EntityRenderer {
   public:
    explicit TerrainRenderer(StaticShader *shaderProgram) : EntityRenderer(shaderProgram) {}

    void render(const std::vector<Terrain> &terrains, const LightCollection &lights);
};

#endif  // DAFT_GAMEENGINE_TERRAINRENDERER_HPP
