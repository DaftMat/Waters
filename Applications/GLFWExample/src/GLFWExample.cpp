//
// Created by mathis on 24/05/2020.
//
#include "GLFWExample.hpp"
#include "GLFWWindow.hpp"
#include <Core/Log.hpp>
#include <Minimal-Engine/Geometry/Primitives.hpp>
#include <Minimal-Engine/Material/PerlinNoise/Noise.hpp>
#include <iostream>

GLFWExample::GLFWExample() {
    init( 1600, 900 );

    auto& renderer = *m_renderer;
    GLFWWindow::setFramebufferCallback(
        [&renderer]( int width, int height ) { renderer.resize( width, height ); } );
    auto& camera = m_camera;
    GLFWWindow::setMouseMoveCallback( [&camera]( float xpos, float ypos ) {
        camera.processMouseMove( glm::vec2{ xpos, ypos } );
    } );
    GLFWWindow::setMousePressCallback( [&camera]( float xpos, float ypos ) {
        camera.processMousePress( glm::vec2{ xpos, ypos } );
    } );
    GLFWWindow::setMouseReleaseCallback( [&camera]() { camera.processMouseRelease(); } );
    GLFWWindow::setMouseScrollCallback(
        [&camera]( float offset ) { camera.processMouseScroll( offset ); } );

    loadExampleScene();
    APP_INFO( "Application created." );
}

void GLFWExample::moveCamera( float dt ) {
    if ( m_window->isPressed( GLFW_KEY_W ) )
        m_camera.processMovement( Camera::Movement::FRONT, dt );
    if ( m_window->isPressed( GLFW_KEY_S ) ) m_camera.processMovement( Camera::Movement::BACK, dt );
    if ( m_window->isPressed( GLFW_KEY_A ) ) m_camera.processMovement( Camera::Movement::LEFT, dt );
    if ( m_window->isPressed( GLFW_KEY_D ) )
        m_camera.processMovement( Camera::Movement::RIGHT, dt );
    if ( m_window->isPressed( GLFW_KEY_SPACE ) )
        m_camera.processMovement( Camera::Movement::UP, dt );
    if ( m_window->isPressed( GLFW_KEY_X ) ) m_camera.processMovement( Camera::Movement::DOWN, dt );
}

void GLFWExample::loadExampleScene() {
    APP_INFO( "Loading example scene..." );
    auto fun = []( float h ) { return ( 4.f * ( h - 0.5f ) * 2.f ) - 1.f; };
    Noise::init( 256, 4, 0.4f, 2.f, glm::vec3{ 0.f, 0.f, 0.f }, new Perlin( 512 ) );

    HeightMap hmap( {}, fun );
    float size = 10.f;
    for ( int i = 0; i < 7; ++i )
    {
        for ( int j = 0; j < 7; ++j )
        {
            glm::vec2 pos{ float( i - 3 ) * 2.f * size, float( j - 3 ) * 2.f * size };
            int index        = i * 7 + j;
            Noise::xOffset() = float( i * 511 );
            Noise::yOffset() = float( j * 511 );
            hmap             = HeightMap( Noise::generate(), fun );
            m_renderer->addTerrain( Terrain( hmap, size ) );
            m_renderer->terrain( index ).position() = glm::vec3{ pos.x, 0.f, pos.y };
            m_renderer->addWater( Water( 0.03f, 4, size ) );
            m_renderer->water( index ).position() = glm::vec3{ pos.x, 0.f, pos.y };
        }
    }

    m_quadRenderer->addQuad( Quad( -1.f, 1.f, 2.f, 2.f ) ); // screen

    m_quadRenderer->quad( 0 ).setTexture( m_renderer->screenFBO().textures()[0] );
    APP_INFO( "Example scene loaded" );
}

void GLFWExample::draw( double deltatime ) {
    m_renderer->prepare();
    m_renderer->render( m_lights, m_camera, deltatime );

    m_quadRenderer->prepare();
    m_quadRenderer->render();
}

void GLFWExample::run() {
    APP_INFO( "launching application..." );
    m_lastTime = glfwGetTime();
    while ( !m_window->shouldClose() )
    {
        auto currenttime = float( glfwGetTime() );
        auto deltaTime   = currenttime - m_lastTime;
        m_lastTime       = currenttime;
        moveCamera( deltaTime );
        draw( deltaTime );
        m_window->finish();
    }
    APP_INFO( "application got out of main loop" );
}
