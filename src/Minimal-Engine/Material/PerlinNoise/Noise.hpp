//
// Created by mathis on 17/05/2020.
//

#ifndef DAFT_GAMEENGINE_NOISE_HPP
#define DAFT_GAMEENGINE_NOISE_HPP

#include "Perlin.hpp"
#include <vector>

class Noise
{
  public:
    static std::vector<float> generate( float scale,
                                        int octaves,
                                        float persistence,
                                        float lacunarity,
                                        float offset,
                                        const Perlin& perlin );

  private:
    static float invlerp( float a, float b, float v ) { return ( v - a ) / ( b - a ); }
};

#endif // DAFT_GAMEENGINE_NOISE_HPP
