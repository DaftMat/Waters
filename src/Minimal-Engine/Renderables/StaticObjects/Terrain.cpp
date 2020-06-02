//
// Created by mathis on 31/05/2020.
//
#include <Minimal-Engine/Geometry/Primitives.hpp>
#include "Terrain.hpp"

Terrain::Terrain(int resolution, float size) {
    m_mesh = Primitives::plane(resolution, size);
    init(size);
}

Terrain::Terrain(const HeightMap &hmap, float size) {
    m_mesh = Primitives::plane(hmap, size);
    init(size);
}

void Terrain::init(float size) {
    m_material.addSetting( "shininess", 1.f );
    m_material.addSetting( "reflectivity", 0.01f );
    m_material.addSetting( "tileFactor", size / 4.f );

}
