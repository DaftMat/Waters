//
// Created by mathis on 17/05/2020.
//

#include "FrameBuffer.hpp"
#include <iostream>
#include <Core/Log.hpp>

FrameBuffer::FrameBuffer( int width, int height, int numSamples ) :
    m_width{ width }, m_height{ height }, m_numSamples{ numSamples } {
    glGenFramebuffers( 1, &m_fbo );
}

FrameBuffer::~FrameBuffer() {
    for ( GLuint& b : m_buffers )
    {
        glDeleteRenderbuffers( 1, &b );
    }
    for ( GLuint& t : m_textures )
    {
        glDeleteTextures( 1, &t );
    }
    glDeleteFramebuffers( 1, &m_fbo );
}

void FrameBuffer::addColorBuffer() {
    if ( m_num_color > GL_COLOR_ATTACHMENT31 ) return;
    glBindFramebuffer( GL_FRAMEBUFFER, m_fbo );
    GLuint rbo;
    glGenRenderbuffers( 1, &rbo );
    glBindRenderbuffer( GL_RENDERBUFFER, rbo );
    if ( m_numSamples == 1 )
        glRenderbufferStorage( GL_RENDERBUFFER, GL_RGB, m_width, m_height );
    else
        glRenderbufferStorageMultisample(
            GL_RENDERBUFFER, m_numSamples, GL_RGB, m_width, m_height );
    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_num_color++, GL_RENDERBUFFER, rbo );
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    m_buffers.push_back( rbo );
}

void FrameBuffer::addDepthBuffer() {
    if ( m_depth ) return;
    glBindFramebuffer( GL_FRAMEBUFFER, m_fbo );
    GLuint rbo;
    glGenRenderbuffers( 1, &rbo );
    glBindRenderbuffer( GL_RENDERBUFFER, rbo );
    if ( m_numSamples == 1 )
        glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height );
    else
        glRenderbufferStorageMultisample(
            GL_RENDERBUFFER, m_numSamples, GL_DEPTH_COMPONENT, m_width, m_height );
    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo );
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    m_depth = true;
    m_buffers.push_back( rbo );
}

void FrameBuffer::addStencilBuffer() {
    if ( m_stencil ) return;
    glBindFramebuffer( GL_FRAMEBUFFER, m_fbo );
    GLuint rbo;
    glGenRenderbuffers( 1, &rbo );
    glBindRenderbuffer( GL_RENDERBUFFER, rbo );
    if ( m_numSamples == 1 )
        glRenderbufferStorage( GL_RENDERBUFFER, GL_STENCIL_INDEX, m_width, m_height );
    else
        glRenderbufferStorageMultisample(
            GL_RENDERBUFFER, m_numSamples, GL_STENCIL_INDEX, m_width, m_height );
    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo );
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    m_stencil = true;
    m_buffers.push_back( rbo );
}

void FrameBuffer::addDepthStencilBuffer() {
    if ( m_stencil_depth ) return;
    glBindFramebuffer( GL_FRAMEBUFFER, m_fbo );
    GLuint rbo;
    glGenRenderbuffers( 1, &rbo );
    glBindRenderbuffer( GL_RENDERBUFFER, rbo );
    if ( m_numSamples == 1 )
        glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height );
    else
        glRenderbufferStorageMultisample(
            GL_RENDERBUFFER, m_numSamples, GL_DEPTH24_STENCIL8, m_width, m_height );
    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo );
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    m_stencil_depth = true;
    m_buffers.push_back( rbo );
}

void FrameBuffer::addColorTexture() {
    if ( m_num_color > GL_COLOR_ATTACHMENT31 ) return;
    glBindFramebuffer( GL_FRAMEBUFFER, m_fbo );
    GLuint tex;
    glGenTextures( 1, &tex );
    glBindTexture( GL_TEXTURE_2D, tex );
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_num_color++, GL_TEXTURE_2D, tex, 0 );
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    m_textures.push_back( tex );
}

void FrameBuffer::addDepthTexture() {
    if ( m_depth ) return;
    glBindFramebuffer( GL_FRAMEBUFFER, m_fbo );
    GLuint tex;
    glGenTextures( 1, &tex );
    glBindTexture( GL_TEXTURE_2D, tex );
    glTexImage2D( GL_TEXTURE_2D,
                  0,
                  GL_DEPTH_COMPONENT32,
                  m_width,
                  m_height,
                  0,
                  GL_DEPTH_COMPONENT,
                  GL_FLOAT,
                  nullptr );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex, 0 );
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    m_depth = true;
    m_textures.push_back( tex );
}

void FrameBuffer::addStencilTexture() {
    if ( m_stencil ) return;
    glBindFramebuffer( GL_FRAMEBUFFER, m_fbo );
    GLuint tex;
    glGenTextures( 1, &tex );
    glBindTexture( GL_TEXTURE_2D, tex );
    glTexImage2D( GL_TEXTURE_2D,
                  0,
                  GL_STENCIL_INDEX16,
                  m_width,
                  m_height,
                  0,
                  GL_STENCIL_INDEX,
                  GL_INT,
                  nullptr );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, tex, 0 );
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    m_stencil = true;
    m_textures.push_back( tex );
}

void FrameBuffer::addDepthStencilTexture() {
    if ( m_stencil_depth ) return;
    glBindFramebuffer( GL_FRAMEBUFFER, m_fbo );
    GLuint tex;
    glGenTextures( 1, &tex );
    glBindTexture( GL_TEXTURE_2D, tex );
    glTexImage2D( GL_TEXTURE_2D,
                  0,
                  GL_DEPTH24_STENCIL8,
                  m_width,
                  m_height,
                  0,
                  GL_DEPTH24_STENCIL8,
                  GL_FLOAT,
                  nullptr );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, tex, 0 );
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    m_stencil_depth = true;
    m_textures.push_back( tex );
}

void FrameBuffer::prepare() const {
    glBindFramebuffer( GL_FRAMEBUFFER, m_fbo );
    if ( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
    {
        glBindFramebuffer( GL_FRAMEBUFFER, 0 );
        ENGINE_ERROR("ERROR:FRAMEBUFFER: Framebuffer is not complete.");
        return;
    }
    glViewport( 0, 0, m_width, m_height );
}

void FrameBuffer::unbind(int width, int height) const {
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    glViewport( 0, 0, width, height );
}

void FrameBuffer::resolve( int width, int height, int index ) {
    if ( index < 0 ) index = 0;
    if ( index > m_num_color - 1 ) index = m_num_color - 1;
    glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );
    glBindFramebuffer( GL_READ_FRAMEBUFFER, m_fbo );
    glReadBuffer( GL_COLOR_ATTACHMENT0 + index );
    glDrawBuffer( GL_BACK );
    glBlitFramebuffer( 0,
                       0,
                       m_width,
                       m_height,
                       0,
                       0,
                       width,
                       height,
                       GL_COLOR_BUFFER_BIT,
                       GL_NEAREST );
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void FrameBuffer::resolve( FrameBuffer& frameBuffer, int index ) {
    if ( index < 0 ) index = 0;
    if ( index > m_num_color - 1 ) index = m_num_color - 1;
    glBindFramebuffer( GL_DRAW_FRAMEBUFFER, frameBuffer.m_fbo );
    glBindFramebuffer( GL_READ_FRAMEBUFFER, m_fbo );
    glReadBuffer( GL_COLOR_ATTACHMENT0 + index );
    glBlitFramebuffer( 0,
                       0,
                       m_width,
                       m_height,
                       0,
                       0,
                       frameBuffer.m_width,
                       frameBuffer.m_height,
                       GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
                       GL_NEAREST );
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void FrameBuffer::drawBuffers() {
    glBindFramebuffer( GL_FRAMEBUFFER, m_fbo );
    auto* bufs = new GLuint[m_num_color];
    for ( int i = 0; i < m_num_color; ++i )
        bufs[i] = GL_COLOR_ATTACHMENT0 + i;
    glDrawBuffers( m_num_color, bufs );
    delete[] bufs;
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}
