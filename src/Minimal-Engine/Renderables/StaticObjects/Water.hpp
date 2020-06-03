//
// Created by mathis on 02/06/2020.
//
#pragma once


#include "Terrain.hpp"

class Water : public Terrain {
public:
    explicit Water(float speed = 0.03f, int resolution = 128, float size = 10.f);

    void move(double deltatime);

private:
    float m_speed;
    float m_offset{0};
};
