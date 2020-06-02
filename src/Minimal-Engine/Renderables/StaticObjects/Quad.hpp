//
// Created by mathis on 02/06/2020.
//
#pragma once


#include <Minimal-Engine/Renderables/Renderable.hpp>

class Quad : public Renderable {
public:
    Quad(float x, float y, float width, float height);

    void setTexture(int id) { m_material.texture("quadTexture").id() = id; }
};
