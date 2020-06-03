//
// Created by mathis on 23/05/2020.
//
#define STB_IMAGE_IMPLEMENTATION

#include "Loader.hpp"
#include <Core/Log.hpp>

#include <stb/stb_image.h>

Mesh Loader::loadMesh( const std::vector<Mesh::Vertex>& vertices,
                       const std::vector<GLuint>& indices ) {
    GLuint vao, vbo, ebo;
    glGenVertexArrays( 1, &vao );
    glGenBuffers( 1, &vbo );
    glGenBuffers( 1, &ebo );

    glBindVertexArray( vao );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER,
                  vertices.size() * sizeof( Mesh::Vertex ),
                  vertices.data(),
                  GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER,
                  indices.size() * sizeof( GLuint ),
                  indices.data(),
                  GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Mesh::Vertex ), (void*)nullptr );
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, sizeof( Mesh::Vertex ), (void*)offsetof( Mesh::Vertex, normal ) );
    glVertexAttribPointer( 2,
                           2,
                           GL_FLOAT,
                           GL_FALSE,
                           sizeof( Mesh::Vertex ),
                           (void*)offsetof( Mesh::Vertex, texCoords ) );

    glBindVertexArray( 0 );
    m_vaos.push_back( vao );
    m_vbos.push_back( vbo );
    m_vbos.push_back( ebo );
    return Mesh( vao, indices.size() );
}

void Loader::clean() {
    for ( auto& vao : m_vaos )
        glDeleteVertexArrays( 1, &vao );
    for ( auto& vbo : m_vbos )
        glDeleteBuffers( 1, &vbo );
    for ( auto& tex : m_texs )
        glDeleteTextures( 1, &tex );
}

Texture Loader::loadTexture( const std::string& name, const std::string& path ) {
    GLuint id;
    glGenTextures( 1, &id );

    int width, height, numChannels;
    unsigned char* data = stbi_load( path.c_str(), &width, &height, &numChannels, 0 );
    if ( data )
    {
        GLenum colorFormat;
        if ( numChannels == 1 )
            colorFormat = GL_RED;
        else if ( numChannels == 3 )
            colorFormat = GL_RGB;
        else if ( numChannels == 4 )
            colorFormat = GL_RGBA;

        glBindTexture( GL_TEXTURE_2D, id );

        glTexImage2D(
            GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data );
        glGenerateMipmap( GL_TEXTURE_2D );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    }
    else
    { ENGINE_ERROR( "Failed to load texture {0}", path ); }
    stbi_image_free( data );
    m_texs.push_back( id );

    return Texture( name, id );
}

std::vector<GLuint> Loader::m_vaos{};
std::vector<GLuint> Loader::m_vbos{};
std::vector<GLuint> Loader::m_texs{};