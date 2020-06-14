//
// Created by mathis on 09/05/2020.
//

#ifndef DAFT_GAMEENGINE_TEXTURE_HPP
#define DAFT_GAMEENGINE_TEXTURE_HPP

#include <Core/NonCopyable.hpp>
#include <Core/OpenGL.hpp>
#include <string>

/** texture class.
 * loads an image into an opengl texture.
 */
class Texture : public wtr::Core::NonCopyable {
   public:
    explicit Texture(std::string name) noexcept : m_id{0}, m_name{std::move_if_noexcept(name)} {}
    ~Texture() {
        if (m_isValid) glDeleteTextures(1, &m_id);
        m_isValid = false;
    }

    Texture(std::string name, std::string path);

    Texture(std::string name, const std::array<std::string, 6> &paths);

    Texture(Texture &&other) noexcept : m_id{other.m_id}, m_name{std::move_if_noexcept(other.m_name)} {
        other.m_isValid = false;
    }
    Texture &operator=(Texture &&other) noexcept;

    /** Binds the texture to the current opengl GL_TEXTURE
     *
     */
    void bind(GLenum textureType = GL_TEXTURE_2D) const;

    /** name getter.
     *
     * @return texture's name.
     */
    [[nodiscard]] const std::string &name() const { return m_name; }

    /** id getter.
     *
     * @return texture's ID.
     */
    [[nodiscard]] GLuint id() const { return m_id; }

    GLuint &id() { return m_id; }

   private:
    GLuint m_id;
    std::string m_name;
    bool m_isValid{false};
};

#endif  // DAFT_GAMEENGINE_TEXTURE_HPP
