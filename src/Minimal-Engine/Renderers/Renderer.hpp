//
// Created by mathis on 01/06/2020.
//
#pragma once
#include <API.hpp>

#include <Core/OpenGL.hpp>
#include <Minimal-Engine/Renderables/Lights/LightCollection.hpp>
#include <Minimal-Engine/Renderables/Cameras/Camera.hpp>
#include <Minimal-Engine/Renderables/StaticObjects/Terrain.hpp>
#include <Minimal-Engine/Renderers/EntityRenderers/TerrainRenderer.hpp>
#include <Minimal-Engine/Renderers/EntityRenderers/WaterRenderer.hpp>
#include <Minimal-Engine/Renderables/StaticObjects/Water.hpp>

class Renderer {
public:
    explicit Renderer( int width, int height, float near                = 0.1f,
                             float far                 = 300.f,
                             float fogDensity          = 0.007f,
                             float fogGradient         = 1.5f,
                             const glm::vec3& skyColor = { 0.49f, 0.89f, 0.98f } );

    void prepare() const;

    void render(const LightCollection &lights, const Camera &camera);

    void addTerrain(const Terrain &terrain) { m_terrains.push_back(terrain); }

    void addWater(const Water &water) { m_waters.push_back(water); }

    void resize(int width, int height);

    [[nodiscard]] int width() const { return m_width; }

    [[nodiscard]] int height() const { return m_height; }

    [[nodiscard]] const TerrainRenderer &terrainRenderer() const { return *m_terrainRenderer; }

    [[nodiscard]] const WaterRenderer &waterRenderer() const { return *m_waterRenderer; }

private:
    static void initGL();
    void clearGL() const;
    static void enableClipDistance(int index = 0) { glEnable(GL_CLIP_DISTANCE0+index); }
    static void disableClipDistance(int index = 0) { glDisable(GL_CLIP_DISTANCE0+index); }

    std::unique_ptr<TerrainRenderer> m_terrainRenderer{nullptr};
    std::unique_ptr<WaterRenderer> m_waterRenderer{nullptr};

    std::vector<Terrain> m_terrains;
    std::vector<Water> m_waters;

    int m_width, m_height;
    float m_near, m_far, m_fogDensity, m_fogGradient;
    glm::vec3 m_skyColor;
};
