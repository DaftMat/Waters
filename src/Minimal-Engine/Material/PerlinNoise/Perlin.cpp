//
// Created by mathis on 15/05/2020.
//

#include "Perlin.hpp"

#include <Core/Random.hpp>

Perlin::Perlin(int size, int seed) {
    if (size < 65) size = 65;
    wtr::Core::Random::seed(seed);
    for (int i = 0; i < size; ++i) p.push_back((int)wtr::Core::Random::get(0, 63));
}

float Perlin::noise(float x, float y, float z) const {
    int X = (int)glm::floor(x) & 63;
    int Y = (int)glm::floor(y) & 63;
    int Z = (int)glm::floor(z) & 63;
    x -= glm::floor(x);
    y -= glm::floor(y);
    z -= glm::floor(z);
    float u = fade(x);
    float v = fade(y);
    float w = fade(z);
    const int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
    const int B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

    float res = lerp(w,
                     lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)),
                          lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))),
                     lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)),
                          lerp(u, grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1))));
    return res;
}

float Perlin::grad(int hash, float x, float y, float z) {
    int h = hash & 15;
    float u = h < 8 ? x : y, v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}