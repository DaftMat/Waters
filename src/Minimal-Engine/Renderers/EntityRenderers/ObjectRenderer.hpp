//
// Created by mathis on 06/06/2020.
//
#pragma once

#include <Minimal-Engine/Renderers/EntityRenderers/EntityRenderer.hpp>
#include <Minimal-Engine/Renderables/StaticObjects/Object.hpp>

class ObjectRenderer : public EntityRenderer {
public:
    explicit ObjectRenderer(StaticShader *staticShader) : EntityRenderer(staticShader) {}

    void render(const std::vector<Object> &objects, const LightCollection &lights);
};
