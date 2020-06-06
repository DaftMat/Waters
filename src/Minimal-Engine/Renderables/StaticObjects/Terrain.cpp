//
// Created by mathis on 31/05/2020.
//
#include "Terrain.hpp"
#include <Core/Log.hpp>
#include <Minimal-Engine/Geometry/Primitives.hpp>

Terrain::Terrain( int resolution, float size ) : m_hmap {std::vector<float>(resolution * resolution, 0.f)}, m_size {size}, m_resolution { resolution } {
    m_mesh      = Primitives::plane( resolution, size );
    m_minHeight = m_maxHeight = 0.f;
    init( size );
}

Terrain::Terrain( const HeightMap& hmap, float size ) : m_hmap { hmap }, m_size {size}, m_resolution { hmap.size() } {
    m_mesh      = Primitives::plane( hmap, size );
    m_minHeight = hmap.getFun()( 0.f );
    m_maxHeight = hmap.getFun()( 1.f );
    init( size );
}

void Terrain::init( float size ) {
    m_material.addSetting( "minHeight", m_minHeight );
    m_material.addSetting( "maxHeight", m_maxHeight );
    m_material.addSetting( "numLayers", 0 );
    m_material.addSetting( "shininess", 1.f );
    m_material.addSetting( "reflectivity", 0.01f );
    m_material.addSetting( "tileFactor", int( size ) );
    addTextureLayer( TextureLayer( "resources/textures/mudwater.jpg", 0.f, 0.15f ) );
    addTextureLayer( TextureLayer( "resources/textures/mud.png", 0.5f, 0.3f ) );
    addTextureLayer( TextureLayer( "resources/textures/grass.png", 0.6f, 0.2f ) );
    // addTextureLayer(TextureLayer("resources/textures/snow.jpg", 0.75f, 0.15f));
}

void Terrain::addTextureLayer( const Terrain::TextureLayer& textureLayer ) {
    std::string name = "texLayers[" + std::to_string( m_numLayers++ ) + "]";
    m_material.addTexture( Loader::loadTexture( name + ".texture", textureLayer.path ) );
    m_material.addSetting( name + ".startHeight", textureLayer.startHeight );
    m_material.addSetting( name + ".blend", textureLayer.blend );
    m_material.setSetting( "numLayers", m_numLayers );
}

float Terrain::getHeight(float x, float y) const {
    float xTerrain = x - m_position.x;// - m_size;
    float yTerrain = y - m_position.z;// - m_size;
    float gridSquare = 2.f * m_size / float(m_resolution - 1);
    auto xGrid = int(glm::floor(xTerrain / gridSquare));
    auto yGrid = int(glm::floor(yTerrain / gridSquare));
    float xCoord = mod(xTerrain, gridSquare) / gridSquare;
    float yCoord = mod(yTerrain, gridSquare) / gridSquare;
    float ret;
    if (xCoord <= (1 - yCoord)) {
        ret = barerp(glm::vec3 {0.f, m_hmap(xGrid, yGrid), 0.f},
                glm::vec3 {1.f, m_hmap(xGrid + 1, yGrid), 0.f},
                glm::vec3 {0.f, m_hmap(xGrid, yGrid + 1), 1.f},
                glm::vec2 {xCoord, yCoord});
    } else {
        ret = barerp(glm::vec3{1.f, m_hmap(xGrid + 1, yGrid), 0.f},
                glm::vec3 {1.f, m_hmap(xGrid + 1, yGrid + 1), 1.f},
                glm::vec3 {0.f, m_hmap(xGrid, yGrid + 1), 1.f},
                glm::vec2 {xCoord, yCoord});
    }
    return ret;
}

float Terrain::barerp(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec2 &pos) {
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

float Terrain::mod(float a, float b) {
    float ret = glm::abs(a);
    b = glm::abs(b);

    while (ret >= b)
        ret -= b;

    if (a < 0)
        ret = -ret;

    return ret;
}
