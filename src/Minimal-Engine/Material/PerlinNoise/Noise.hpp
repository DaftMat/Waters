//
// Created by mathis on 17/05/2020.
//

#ifndef DAFT_GAMEENGINE_NOISE_HPP
#define DAFT_GAMEENGINE_NOISE_HPP

#include "Perlin.hpp"
#include <memory>
#include <vector>

class Noise
{
  public:
    static void init( float scale,
                      int octaves,
                      float persistence,
                      float lacunarity,
                      const glm::vec3& offset,
                      Perlin* perlin );

    static std::vector<float> generate();

    [[nodiscard]] static float& scale() { return m_scale; }

    [[nodiscard]] static int& octaves() { return m_octaves; }

    [[nodiscard]] static float& persistence() { return m_persistence; }

    [[nodiscard]] static float& lacunarity() { return m_lacunarity; }

    [[nodiscard]] static float& xOffset() { return m_xOffset; }

    [[nodiscard]] static float& yOffset() { return m_yOffset; }

    [[nodiscard]] static float& zOffset() { return m_zOffset; }

    static void setPerlin( Perlin* perlin ) { m_perlin.reset( perlin ); }

    [[nodiscard]] static const Perlin& perlin() { return *m_perlin; }

  private:
    static float invlerp( float a, float b, float v ) { return ( v - a ) / ( b - a ); }

    static float m_scale;
    static int m_octaves;
    static float m_persistence, m_lacunarity;
    static float m_xOffset, m_yOffset, m_zOffset;
    static std::unique_ptr<Perlin> m_perlin;
};

#endif // DAFT_GAMEENGINE_NOISE_HPP
