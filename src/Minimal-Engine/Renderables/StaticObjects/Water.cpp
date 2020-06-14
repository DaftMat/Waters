//
// Created by mathis on 02/06/2020.
//

#include "Water.hpp"

#include <Minimal-Engine/Geometry/Primitives.hpp>

Water::Water(float speed, int resolution, float size) : m_speed{speed} {
    m_mesh = Primitives::plane(resolution, size);
    m_material.addTexture(Texture("reflectionTex"));
    m_material.addTexture(Texture("refractionTex"));
    m_material.addTexture(Texture("refractionDepth"));
    m_material.addTexture(Texture("dudvMap", "resources/textures/waterDUDV.png"));
    m_material.addTexture(Texture("normalMap", "resources/textures/waterNormal.png"));
    m_material.addSetting("distortionForce", 0.04f);
    m_material.addSetting("near", 0.1f);
    m_material.addSetting("far", 300.f);
    m_material.addSetting("offset", 0.f);
    m_material.addSetting("shininess", 20.f);
    m_material.addSetting("reflectivity", 0.5f);
    m_material.addSetting("tileFactor", int(size / 4.f));
}

void Water::move(double deltatime) {
    m_offset += m_speed * float(deltatime);
    if (m_offset > 1.f) m_offset = 0.f;
    m_material.setSetting("offset", m_offset);
}
