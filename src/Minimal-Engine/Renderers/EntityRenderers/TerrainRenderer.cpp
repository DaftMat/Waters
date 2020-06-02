//
// Created by mathis on 13/05/2020.
//

#include "TerrainRenderer.hpp"

void TerrainRenderer::render( const std::vector<Terrain>& terrains,
                              const LightCollection& lights ) {
    setLights( lights );
    for ( const auto& t : terrains )
    {
        m_shaderProgram->setMat4( "model", t.model() );
        m_shaderProgram->setMaterial( t.material(), "terrainMat" );
        m_shaderProgram->setInt("entityType", 1);
        t.prepare();
        t.render( GL_TRIANGLES );
        t.unbind();
    }
    m_shaderProgram->clearLights();
}
