//
// Created by mathis on 09/05/2020.
//

#ifndef DAFT_GAMEENGINE_MESH_HPP
#define DAFT_GAMEENGINE_MESH_HPP
#include <API.hpp>

#include <Core/OpenGL.hpp>
#include <vector>

/** mesh class.
 * a triangle based mesh that associates geometry and topology
 */
class ENGINE_API Mesh ///TODO: make noncopyable and make it deallocate its vao.
{
  public:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    Mesh() = default;
    Mesh( GLuint vao, GLuint vbo, GLuint ebo, GLuint numVertex ) : m_vao{ vao }, m_vbo { vbo }, m_ebo { ebo }, m_numVertex{ numVertex } {}
    ~Mesh() = default;

    bool operator==(const Mesh &other) const { return m_vao == other.m_vao; }
    bool operator==(Mesh &&other) const { return m_vao == other.m_vao; }

    Mesh(const Mesh &mesh) = default;

    void prepare() const;

    void render( GLuint type ) const;

    void unbind() const;

    [[nodiscard]] GLuint& vao() { return m_vao; }

    [[nodiscard]] GLuint& vbo() { return m_vbo; }

    [[nodiscard]] GLuint& ebo() { return m_ebo; }


  private:
    GLuint m_vao{ 0 }, m_ebo{0}, m_vbo{0}, m_numVertex{ 0 };
};

#endif // DAFT_GAMEENGINE_MESH_HPP
