//
// Created by mathis on 31/05/2020.
//
#pragma once

#include <API.hpp>

#include <Core/OpenGL.hpp>
#include <Minimal-Engine/Geometry/Mesh.hpp>
#include <Minimal-Engine/Material/Material.hpp>
#include <utility>

/** Base class for all renderable objects.
 *
 */
class ENGINE_API Renderable
{
  public:
    enum Type { OBJECT = 0, TERRAIN, WATER };

    Renderable()          = default;
    virtual ~Renderable() = default;

    bool operator==(const Renderable &other) const { return m_mesh == other.m_mesh; }
    bool operator==(Renderable &&other) const { return m_mesh == other.m_mesh; }

    void prepare() const;

    void render( GLuint type ) const;

    void unbind() const;

    [[nodiscard]] virtual glm::mat4 model() const { return glm::mat4{ 1.f }; }

    [[nodiscard]] const Mesh& mesh() const { return m_mesh; }

    Mesh& mesh() { return m_mesh; }

    [[nodiscard]] const Material& material() const { return m_material; };

    Material& material() { return m_material; };

    virtual void toggleVisible();

    [[nodiscard]] bool isVisible() const { return m_visible; }

  protected:
    virtual Mesh generateMesh() = 0;

    bool m_visible;
    Mesh m_mesh;
    Material m_material;
};
