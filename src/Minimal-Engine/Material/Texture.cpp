//
// Created by mathis on 09/05/2020.
//

#include "Texture.hpp"
#include <string>

Texture::Texture( std::string name, GLuint id ) : m_name{ std::move( name ) }, m_id{ id } {}

void Texture::bind() const {
    glBindTexture( GL_TEXTURE_2D, m_id );
}