//
// Created by mathis on 13/05/2020.
//

#ifndef DAFT_GAMEENGINE_ENTITYRENDERER_HPP
#define DAFT_GAMEENGINE_ENTITYRENDERER_HPP

#include <Minimal-Engine/Renderables/Lights/LightCollection.hpp>
#include <Minimal-Engine/ShaderPrograms/StaticShader.hpp>
#include <memory>

class EntityRenderer
{
  public:
    /** Default constructor (no shader).
     *
     */
    EntityRenderer() = default;

    /** Constructor.
     *
     * @param shaderProgram - associated shaderProgram.
     * @param projection - projection matrix.
     */
    explicit EntityRenderer( StaticShader* shaderProgram ) : m_shaderProgram{ shaderProgram } {}

    /** Prepares the renderer to render.
     *
     */
    void prepare() const;

    /** Load camera/viewport transformation matrices to the inner shader.
     *
     * @param view - camera's view matrix.
     * @param projection - viewport's projection matrix.
     */
    void loadMatrices( const glm::mat4& view, const glm::mat4& projection ) const;

    void loadFog( float density, float gradient ) const;

    void loadSky( const glm::vec3& skyColor ) const {
        m_shaderProgram->setVec3( "skyColor", skyColor );
    }

    void setClipPlane( const glm::vec4& plane ) const {
        m_shaderProgram->setVec4( "clipPlane", plane );
    }

    void unbind() const { m_shaderProgram->stop(); }

    void setShader( const char* vertex, const char* fragment );

  protected:
    void setLights( const LightCollection& lights ) const;

    std::unique_ptr<StaticShader> m_shaderProgram{ nullptr };
};

#endif // DAFT_GAMEENGINE_ENTITYRENDERER_HPP
