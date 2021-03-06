//
// Created by mathis on 01/06/2020.
//
#pragma once
#include <API.hpp>
#include <Core/OpenGL.hpp>
#include <Minimal-Engine/Renderables/Cameras/Camera.hpp>
#include <Minimal-Engine/Renderables/DynamicObjects/Player.hpp>
#include <Minimal-Engine/Renderables/Lights/LightCollection.hpp>
#include <Minimal-Engine/Renderables/StaticObjects/Terrain.hpp>
#include <Minimal-Engine/Renderables/StaticObjects/TerrainGrid.hpp>
#include <Minimal-Engine/Renderables/StaticObjects/Water.hpp>
#include <Minimal-Engine/Renderers/EntityRenderers/ObjectRenderer.hpp>
#include <Minimal-Engine/Renderers/EntityRenderers/SkyRenderer.hpp>
#include <Minimal-Engine/Renderers/EntityRenderers/TerrainRenderer.hpp>
#include <Minimal-Engine/Renderers/EntityRenderers/WaterRenderer.hpp>
#include <Minimal-Engine/Renderers/FrameBuffers/MultiPass/MultiSamplePass.hpp>

class Renderer {
   public:
    explicit Renderer(int width, int height, float near = 0.1f, float far = 1000.f, float fogDensity = 0.007f,
                      float fogGradient = 1.5f, float terrainSize = 20.f,
                      const glm::vec3 &skyColor = {0.49f, 0.89f, 0.98f});

    void prepare() const;

    void render(const LightCollection &lights, const Camera &camera, double deltatime);

    void addTerrain(int x, int y) { m_terrains.addTerrain(x, y); }

    void addWater(Water water) { m_waters.emplace_back(std::move(water)); }

    void addObject(Object object) { m_objects.emplace_back(std::move(object)); }

    void initPlayer(Player player) { m_player = std::move(player); }

    void resize(int width, int height);

    [[nodiscard]] int width() const { return m_width; }

    [[nodiscard]] int height() const { return m_height; }

    [[nodiscard]] const TerrainRenderer &terrainRenderer() const { return *m_terrainRenderer; }

    [[nodiscard]] const WaterRenderer &waterRenderer() const { return *m_waterRenderer; }

    [[nodiscard]] const ObjectRenderer &objectRenderer() const { return *m_objectRenderer; }

    [[nodiscard]] int numTerrains() const { return m_terrains.size(); }

    [[nodiscard]] int numWaters() const { return m_waters.size(); }

    [[nodiscard]] const TerrainGrid &terrains() const { return m_terrains; }

    [[nodiscard]] TerrainGrid &terrains() { return m_terrains; }

    [[nodiscard]] const Water &water(int index) const { return m_waters[index]; }

    [[nodiscard]] Water &water(int index) { return m_waters[index]; }

    [[nodiscard]] int numObjects() const { return m_objects.size(); }

    [[nodiscard]] const Object &object(int index) const { return m_objects[index]; }

    [[nodiscard]] Object &object(int index) { return m_objects[index]; }

    [[nodiscard]] const Player &player() const { return m_player; }

    [[nodiscard]] Player &player() { return m_player; }

    [[nodiscard]] const FBO &screenFBO() const { return m_renderPass->resultFBO(); }

    [[nodiscard]] const glm::vec3 &skyColor() const { return m_skyColor; }

    [[nodiscard]] glm::vec3 &skyColor() { return m_skyColor; }

    void update(float deltatime);

   private:
    static void initGL();
    void clearGL() const;
    static void enableClipDistance(int index = 0) { glEnable(GL_CLIP_DISTANCE0 + index); }
    static void disableClipDistance(int index = 0) { glDisable(GL_CLIP_DISTANCE0 + index); }
    void renderScene(const glm::mat4 &view, const glm::mat4 &proj, const LightCollection &lights,
                     const glm::vec4 &clipPlane = glm::vec4{0.f});

    std::unique_ptr<TerrainRenderer> m_terrainRenderer{nullptr};
    std::unique_ptr<WaterRenderer> m_waterRenderer{nullptr};
    std::unique_ptr<ObjectRenderer> m_objectRenderer{nullptr};
    std::unique_ptr<SkyRenderer> m_skyRenderer{nullptr};

    TerrainGrid m_terrains;
    std::vector<Water> m_waters;
    std::vector<Object> m_objects;

    Player m_player{Mesh{}};

    std::unique_ptr<MultiSamplePass> m_renderPass{nullptr};

    int m_width, m_height;
    float m_near, m_far, m_fogDensity, m_fogGradient;
    glm::vec3 m_skyColor;
};
