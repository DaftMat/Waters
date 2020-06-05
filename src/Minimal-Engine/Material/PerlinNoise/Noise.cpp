//
// Created by mathis on 17/05/2020.
//

#include "Noise.hpp"
#include <Core/Random.hpp>

void Noise::init( float scale,
                  int octaves,
                  float persistence,
                  float lacunarity,
                  const glm::vec3& offset,
                  Perlin* perlin ) {
    m_scale       = scale;
    m_octaves     = octaves;
    m_persistence = persistence;
    m_lacunarity  = lacunarity;
    m_xOffset     = offset.x;
    m_yOffset     = offset.y;
    m_zOffset     = offset.z;
    m_perlin.reset( perlin );
}

std::vector<float> Noise::generate() {
    int size = m_perlin->size();
    std::vector<float> map;

    if ( m_scale <= 0.f ) m_scale = 0.0001f;
    float maxPossibleHeight = 0.f;
    float amplitude         = 1.f;

    for ( int i = 0; i < m_octaves; ++i )
    {
        maxPossibleHeight += amplitude;
        amplitude *= m_persistence;
    }

    for ( int y = 0; y < size; ++y )
    {
        for ( int x = 0; x < size; ++x )
        {
            amplitude       = 1.f;
            float frequency = 1.f;
            float height    = 0.f;

            for ( int i = 0; i < m_octaves; ++i )
            {
                float sampleX = ( float( x ) + m_xOffset ) / m_scale * frequency;
                float sampleY = ( float( y ) + m_yOffset ) / m_scale * frequency;
                float sampleZ = m_zOffset / m_scale * frequency;

                height += m_perlin->noise( sampleX, sampleY, sampleZ ) * amplitude;

                amplitude *= m_persistence;
                frequency *= m_lacunarity;
            }

            map.push_back( height );
        }
    }

    for ( auto& h : map )
    {
        h = ( h + 1.f ) / ( 2.f * maxPossibleHeight / 2.f );
    }

    return map;
}

float Noise::m_scale{ 0.f };
int Noise::m_octaves{ 0 };
float Noise::m_persistence{ 0.f }, Noise::m_lacunarity{ 0.f };
float Noise::m_xOffset{ 0.f }, Noise::m_yOffset{ 0.f }, Noise::m_zOffset{ 0.f };
std::unique_ptr<Perlin> Noise::m_perlin{ nullptr };