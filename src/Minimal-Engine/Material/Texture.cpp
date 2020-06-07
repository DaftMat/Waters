//
// Created by mathis on 09/05/2020.
//

#include "Texture.hpp"
#include <string>

Texture::Texture( std::string name, GLuint id ) : m_name{ std::move( name ) }, m_id{ id } {}

void Texture::bind(GLenum textureType) const {
    glBindTexture( textureType, m_id );
}