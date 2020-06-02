//
// Created by mathis on 17/05/2020.
//

#include "Noise.hpp"

std::vector<float> Noise::generate( float scale,
                                    int octaves,
                                    float persistence,
                                    float lacunarity,
                                    float offset,
                                    const Perlin& perlin ) {
    int size = perlin.size();
    std::vector<float> map;

    if ( scale <= 0.f ) scale = 0.0001f;

    float maxNoiseHeight = -100000.f;
    float minNoiseHeight = 100000.f;

    for ( int y = 0; y < size; ++y )
    {
        for ( int x = 0; x < size; ++x )
        {
            float amplitude = 1.f;
            float frequency = 1.f;
            float height    = 0.f;

            for ( int i = 0; i < octaves; ++i )
            {
                float sampleX = float( x ) / scale * frequency;
                float sampleY = float( y ) / scale * frequency;
                float sampleZ = offset / scale * frequency;

                height += perlin.noise( sampleX, sampleY, sampleZ ) * amplitude;

                amplitude *= persistence;
                frequency *= lacunarity;
            }

            map.push_back( height );
            if ( height > maxNoiseHeight ) { maxNoiseHeight = height; }
            else if ( height < minNoiseHeight )
            { minNoiseHeight = height; }
        }
    }

    for ( auto& h : map )
    {
        h = invlerp( minNoiseHeight, maxNoiseHeight, h );
    }

    return map;
}