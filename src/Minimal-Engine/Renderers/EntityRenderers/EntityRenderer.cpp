//
// Created by mathis on 13/05/2020.
//

#include "EntityRenderer.hpp"

#include <memory>

void EntityRenderer::prepare() const {
    m_shaderProgram->use();
}

void EntityRenderer::loadMatrices( const glm::mat4& view, const glm::mat4& projection ) const {
    m_shaderProgram->setMat4( "view", view );
    m_shaderProgram->setMat4( "projection", projection );
}

void EntityRenderer::setLights( const LightCollection& lights ) const {
    // add lights to the scene
    for ( const auto& light : lights.pointLights() )
        m_shaderProgram->addLight( light );
    for ( const auto& light : lights.directLights() )
        m_shaderProgram->addLight( light );
}

void EntityRenderer::setShader( const char* vertex, const char* fragment ) {
    m_shaderProgram = std::make_unique<StaticShader>( vertex, fragment );
}

void EntityRenderer::loadFog( float density, float gradient ) const {
    m_shaderProgram->setFloat( "fog_density", density );
    m_shaderProgram->setFloat( "fog_gradient", gradient );
}
