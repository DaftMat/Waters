//
// Created by mathis on 02/06/2020.
//
#pragma once

#include <Minimal-Engine/Renderables/StaticObjects/Water.hpp>
#include <Minimal-Engine/Renderers/FrameBuffers/FBO/FBO.hpp>

#include "EntityRenderer.hpp"

class WaterRenderer : public EntityRenderer {
   public:
    explicit WaterRenderer(StaticShader *shader);
    ~WaterRenderer();

    void render(std::vector<Water> &waters, const LightCollection &lights, double deltatime);

    [[nodiscard]] const FBO &refractionFBO() const { return *m_refractionFbo; }
    [[nodiscard]] const FBO &reflectionFBO() const { return *m_reflectionFbo; }

   private:
    std::unique_ptr<FBO> m_refractionFbo{nullptr}, m_reflectionFbo{nullptr};
};
