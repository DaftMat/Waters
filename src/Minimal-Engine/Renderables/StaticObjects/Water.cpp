//
// Created by mathis on 02/06/2020.
//

#include "Water.hpp"

Water::Water(int resolution, float size) : Terrain(resolution, size) {
    m_material.addTexture(Texture("reflectionTex", 0));
    m_material.addTexture(Texture("refractionTex", 0));
    //m_material.addTexture(Texture("dudvMap", 0));
    //m_material.addTexture(Texture("normalMap", 0));
}
