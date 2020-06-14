//
// Created by mathis on 31/05/2020.
//
#pragma once

#include <Minimal-Engine/Loader.hpp>
#include <Minimal-Engine/Material/HeightMap.hpp>

#include "Mesh.hpp"

namespace Primitives {
struct Triangle {
    glm::vec<3, int> indices;
    glm::vec3 normal;
};

Mesh plane(int resolution = 128, float size = 1.f);
Mesh plane(const HeightMap &hmap, float size = 1.f, int lod = 0);
Mesh cube(int resolution = 10, float size = 1.f);
}  // namespace Primitives
