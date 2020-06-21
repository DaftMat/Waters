//
// Created by mathis on 13/05/2020.
//

#ifndef DAFT_GAMEENGINE_TERRAINRENDERER_HPP
#define DAFT_GAMEENGINE_TERRAINRENDERER_HPP

#include <Minimal-Engine/Renderables/Lights/LightCollection.hpp>

#include "EntityRenderer.hpp"

class TerrainGrid;

/** Renderer specially for Terrains
 *
 */
class TerrainRenderer : public EntityRenderer {
   public:
    explicit TerrainRenderer(StaticShader *shaderProgram) : EntityRenderer(shaderProgram) {}

    void render(const TerrainGrid &terrains, const LightCollection &lights);
};

#endif  // DAFT_GAMEENGINE_TERRAINRENDERER_HPP
