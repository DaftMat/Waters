//
// Created by mathis on 14/05/2020.
//

#ifndef PERLINNOISE_PERLINNOISE_HPP
#define PERLINNOISE_PERLINNOISE_HPP

#include <Core/OpenGL.hpp>
#include <vector>

class Perlin
{
  public:
    explicit Perlin( int size, int seed = 2020 );

    float noise( float x, float y, float z ) const;

    int size() const { return p.size(); }

  private:
    static constexpr float fade( float t ) { return t * t * t * ( t * ( t * 6 - 15 ) + 10 ); }
    static constexpr float lerp( float t, float a, float b ) { return a + t * ( b - a ); }
    static float grad( int hash, float x, float y, float z );

    std::vector<int> p;
};

#endif // PERLINNOISE_PERLINNOISE_HPP
