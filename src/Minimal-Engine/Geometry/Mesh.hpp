//
// Created by mathis on 09/05/2020.
//

#ifndef DAFT_GAMEENGINE_MESH_HPP
#define DAFT_GAMEENGINE_MESH_HPP
#include <API.hpp>
#include <Core/NonCopyable.hpp>
#include <Core/OpenGL.hpp>
#include <vector>

/** mesh class.
 * a triangle based mesh that associates geometry and topology
 */
class ENGINE_API Mesh : public wtr::Core::NonCopyable {
   public:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    constexpr Mesh() noexcept = default;
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices) { reset(std::move(vertices), std::move(indices)); }
    explicit Mesh(std::string path) { reset(std::move(path)); }
    ~Mesh() { reset(); };

    bool operator==(const Mesh &other) const { return m_vao == other.m_vao; }
    bool operator==(Mesh &&other) const { return m_vao == other.m_vao; }

    Mesh(Mesh &&other) noexcept
        : m_vao{other.m_vao}, m_vbo{other.m_vbo}, m_ebo{other.m_ebo}, m_numVertex{other.m_numVertex}, isValid{true} {
        other.isValid = false;
    }
    Mesh &operator=(Mesh &&other) noexcept;

    void prepare() const;

    void render(GLuint type) const;

    void unbind() const;

    void reset();

    void reset(std::vector<Vertex> vertices, std::vector<GLuint> indices);

    void reset(std::string path);

    [[nodiscard]] GLuint &vao() { return m_vao; }

    [[nodiscard]] GLuint &vbo() { return m_vbo; }

    [[nodiscard]] GLuint &ebo() { return m_ebo; }

   private:
    GLuint m_vao{0}, m_vbo{0}, m_ebo{0}, m_numVertex{0};
    bool isValid{false};
};

#endif  // DAFT_GAMEENGINE_MESH_HPP
