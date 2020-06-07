//
// Created by mathis on 01/06/2020.
//
#include "Renderer.hpp"
#include <Core/Log.hpp>

Renderer::Renderer( int width,
                    int height,
                    float near,
                    float far,
                    float fogDensity,
                    float fogGradient,
                    const glm::vec3& skyColor ) :
    m_width{ width },
    m_height{ height },
    m_near{ near },
    m_far{ far },
    m_fogDensity{ fogDensity },
    m_fogGradient{ fogGradient },
    m_skyColor{ skyColor } {
    initGL();
    m_terrainRenderer = std::make_unique<TerrainRenderer>(
        new StaticShader( "shaders/blinnphong.vert.glsl", "shaders/blinnphong.frag.glsl" ) );
    m_waterRenderer = std::make_unique<WaterRenderer>(
        new StaticShader( "shaders/blinnphong.vert.glsl", "shaders/blinnphong.frag.glsl" ) );
    m_objectRenderer = std::make_unique<ObjectRenderer>(
            new StaticShader( "shaders/blinnphong.vert.glsl", "shaders/blinnphong.frag.glsl" ) );
    m_skyRenderer = std::make_unique<SkyRenderer>("resources/textures/bluecloud/", far / 2.f);

    m_renderPass = std::make_unique<MultiSamplePass>( 1920, 1080, 32 );

    glViewport( 0, 0, width, height );
    glEnable( GL_MULTISAMPLE );
    glDepthFunc( GL_LESS );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    glFrontFace( GL_CW );
}

void Renderer::prepare() const {
    glEnable( GL_DEPTH_TEST );
    clearGL();
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void Renderer::render( const LightCollection& lights, const Camera& camera, double deltatime ) {
    auto view = camera.getViewMatrix();
    auto proj =
        glm::perspective( camera.getFov(), float( m_width ) / float( m_height ), m_near, m_far );

    enableClipDistance();

    m_waterRenderer->refractionFBO().prepare(); /// to refraction buffer
    clearGL();
    renderScene( view, proj, lights, glm::vec4{ 0.f, -1.f, 0.f, 0.25f } );

    m_waterRenderer->reflectionFBO().prepare(); /// to reflection buffer
    clearGL();
    /// flip camera for reflections
    Camera reflectionCamera = camera;
    reflectionCamera.flip();
    renderScene( reflectionCamera.getViewMatrix(), proj, lights, glm::vec4{ 0.f, 1.f, 0.f, 0.f } );

    disableClipDistance();

    m_renderPass->prepare(); /// to the screen buffer
    clearGL();
    /// Scene
    renderScene( view, proj, lights );
    /// Waters
    m_waterRenderer->prepare();
    m_waterRenderer->loadMatrices( view, proj );
    m_waterRenderer->loadFog( m_fogDensity, m_fogGradient );
    m_waterRenderer->loadSkybox( m_skyRenderer->skybox() );
    m_waterRenderer->render( m_waters, lights, deltatime );
    m_waterRenderer->unbind();
    /// finished
    m_renderPass->unbind( m_width, m_height );
}

void Renderer::resize( int width, int height ) {
    m_width  = width;
    m_height = height;
    glViewport( 0, 0, width, height );
}

void Renderer::initGL() {
    if ( !gladLoadGL() )
    {
        ENGINE_ERROR( "Failed to load OpenGL." );
        exit( -1 );
    }
}

void Renderer::clearGL() const {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor( m_skyColor.r, m_skyColor.g, m_skyColor.b, 1.f );
}

void Renderer::renderScene( const glm::mat4& view,
                            const glm::mat4& proj,
                            const LightCollection& lights,
                            const glm::vec4& clipPlane ) {
    m_terrainRenderer->prepare();
    m_terrainRenderer->loadMatrices( view, proj );
    m_terrainRenderer->loadFog( m_fogDensity, m_fogGradient );
    m_terrainRenderer->loadSkybox( m_skyRenderer->skybox() );
    if ( glm::length( clipPlane ) > 0 ) m_terrainRenderer->setClipPlane( clipPlane );
    m_terrainRenderer->render( m_terrains, lights );
    m_terrainRenderer->unbind();

    m_objectRenderer->prepare();
    m_objectRenderer->loadMatrices(view, proj);
    m_objectRenderer->loadFog(m_fogDensity, m_fogGradient);
    m_objectRenderer->loadSkybox(m_skyRenderer->skybox());
    if (glm::length(clipPlane) > 0) m_objectRenderer->setClipPlane(clipPlane);
    m_objectRenderer->render(m_objects, lights);
    m_objectRenderer->unbind();

    m_skyRenderer->prepare();
    m_skyRenderer->loadMatrices(view, proj);
    m_skyRenderer->render();
    m_skyRenderer->unbind();
}

void Renderer::update(float deltatime) {
    m_skyRenderer->rotate(deltatime);
}
