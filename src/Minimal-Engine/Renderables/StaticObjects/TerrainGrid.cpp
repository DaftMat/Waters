//
// Created by mathis on 08/06/2020.
//
#include "TerrainGrid.hpp"

#include <Minimal-Engine/Material/PerlinNoise/Noise.hpp>

TerrainGrid::TerrainGrid(float size) : m_size{size} {
    Noise::init(120, 6, 0.5f, 2.f, glm::vec3{baseOffset, baseOffset, 0.f}, new Perlin(241));
}

void TerrainGrid::addTerrain(int x, int y) {
    Noise::xOffset() = baseOffset + float(x * (resolution - 1));
    Noise::yOffset() = baseOffset + float(y * (resolution - 1));
    Terrain terrain{HeightMap(Noise::generate(), m_fun), m_size, 0};
    terrain.position() = glm::vec3{float(x) * (2.f * m_size), 0.f, float(y) * (2.f * m_size)};
    glm::vec<2, int> pos{x, y};
    m_terrains.insert(std::make_pair(pos, std::move(terrain)));
}

Terrain &TerrainGrid::terrain(int x, int y) { return m_terrains.at(glm::ivec2{x, y}); }

const Terrain &TerrainGrid::terrain(int x, int y) const { return m_terrains.at(glm::ivec2{x, y}); }

float TerrainGrid::getHeight(float x, float y) const {
    float h = -10000.f;
    for (const auto &t : m_terrains) {
        h = t.second.getHeight(x, y);
        if (h > -1000.f) return h;
    }
    return h;
}

float const TerrainGrid::baseOffset{1000000.f};
int const TerrainGrid::resolution{241};
