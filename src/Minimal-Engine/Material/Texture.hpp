//
// Created by mathis on 09/05/2020.
//

#ifndef DAFT_GAMEENGINE_TEXTURE_HPP
#define DAFT_GAMEENGINE_TEXTURE_HPP

#include <Core/OpenGL.hpp>
#include <string>

/** texture class.
 * loads an image into an opengl texture.
 */
class Texture
{
  public:
    /** Constructor.
     *
     * @param name - name of the texture.
     * @param file - file path of the texture.
     */
    Texture( std::string name, GLuint id );

    /** Binds the texture to the current opengl GL_TEXTURE
     *
     */
    void bind(GLenum textureType = GL_TEXTURE_2D) const;

    /** name getter.
     *
     * @return texture's name.
     */
    [[nodiscard]] const std::string& name() const { return m_name; }

    /** id getter.
     *
     * @return texture's ID.
     */
    [[nodiscard]] GLuint id() const { return m_id; }

    GLuint& id() { return m_id; }

  private:
    GLuint m_id;
    std::string m_name;
};

#endif // DAFT_GAMEENGINE_TEXTURE_HPP
