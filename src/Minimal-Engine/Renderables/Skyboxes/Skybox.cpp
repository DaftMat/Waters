//
// Created by mathis on 07/06/2020.
//
#include "Skybox.hpp"

#include <Minimal-Engine/Geometry/Primitives.hpp>

Skybox::Skybox(const std::string &skyDir, float size, float speed) : m_speed{speed} {
    std::string dir = skyDir;
    if (dir.back() != '/') dir += "/";
    std::for_each(m_faces.begin(), m_faces.end(), [&dir](std::string &e) { e = dir + e + ".jpg"; });
    m_mesh = Primitives::cube(2, size);
    m_material.addTexture(Loader::loadCubeMap("cubeMap", m_faces));
}
