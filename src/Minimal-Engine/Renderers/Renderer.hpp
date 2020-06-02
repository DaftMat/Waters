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

    void resize(int width, int height);

private:
    static void initGL();

    TerrainRenderer m_terrainRenderer;

    std::vector<Terrain> m_terrains;

    int m_width, m_height;
    float m_near, m_far, m_fogDensity, m_fogGradient;
    glm::vec3 m_skyColor;
};
