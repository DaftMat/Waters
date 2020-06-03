//
// Created by mathis on 18/05/2020.
//

#ifndef DAFT_GAMEENGINE_QUADRENDERER_HPP
#define DAFT_GAMEENGINE_QUADRENDERER_HPP

#include <Minimal-Engine/Renderables/StaticObjects/Quad.hpp>
#include <Minimal-Engine/ShaderPrograms/QuadShader.hpp>
#include <memory>

class QuadRenderer
{
  public:
    explicit QuadRenderer();

    void render() const;

    void prepare() const;

    void addQuad( const Quad& quad ) { m_quads.push_back( quad ); }

    Quad& quad( int index ) { return m_quads[index]; }

  private:
    std::vector<Quad> m_quads;
    std::unique_ptr<QuadShader> m_shader{ nullptr };
};

#endif // DAFT_GAMEENGINE_QUADRENDERER_HPP
