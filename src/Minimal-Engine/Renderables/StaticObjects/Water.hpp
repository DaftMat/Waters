//
// Created by mathis on 02/06/2020.
//
#pragma once


#include "Terrain.hpp"

class Water : public Terrain {
public:
    explicit Water(int resolution = 128, float size = 10.f);
};
