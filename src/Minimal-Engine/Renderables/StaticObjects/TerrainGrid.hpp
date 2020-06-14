//
// Created by mathis on 08/06/2020.
//
#pragma once

#include <glm/detail/type_vec2.hpp>
#include <unordered_map>

#include "Terrain.hpp"

class TerrainGrid {
   public:
    explicit TerrainGrid(float size);

    void addTerrain(int x, int y);

    std::vector<Terrain> terrains();

    std::function<float(float)> &fun() { return m_fun; }

    [[nodiscard]] const std::function<float(float)> &fun() const { return m_fun; }

    [[nodiscard]] float getHeight(float x, float y) const;

    [[nodiscard]] int size() const { return m_terrains.size(); }

    /** updates the terrains that are rendered to the scene.
     *
     * @param x - world X position of the player.
     * @param y - world Y position of the player.
     */
    void update(float x, float y);

   private:
    struct KeyFuncs {
        size_t operator()(const glm::ivec2 &k) const { return std::hash<int>()(k.x) ^ std::hash<int>()(k.y); }

        bool operator()(const glm::ivec2 &a, const glm::ivec2 &b) const { return a.x == b.x && a.y == b.y; }
    };

    float m_size;

    std::unordered_map<glm::ivec2, Terrain, KeyFuncs, KeyFuncs> m_terrains;
    std::function<float(float)> m_fun{[](float h) { return h; }};

    static const float baseOffset;
    static const int resolution;
};
