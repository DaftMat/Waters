//
// Created by mathis on 31/05/2020.
//
#include "Terrain.hpp"
#include <Core/Log.hpp>
#include <Minimal-Engine/Geometry/Primitives.hpp>

Terrain::Terrain( int resolution, float size ) {
    m_mesh      = Primitives::plane( resolution, size );
    m_minHeight = m_maxHeight = 0.f;
    init( size );
}

Terrain::Terrain( const HeightMap& hmap, float size ) {
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
