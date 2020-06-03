//
// Created by mathis on 24/05/2020.
//
#pragma once
#include <API.hpp>

#include <Minimal-Engine/Loader.hpp>
#include <Minimal-Engine/Renderers/EntityRenderers/QuadRenderer.hpp>
#include <Minimal-Engine/Renderers/Renderer.hpp>
#include <memory>

/// TODO: if you changed ENGINE_API macro, make sure you update it here.
template <typename WindowType>
class ENGINE_API BaseApplication
{
  public:
    BaseApplication() = default;
    virtual ~BaseApplication() {
        Loader::clean();
        m_renderer.reset();
        m_quadRenderer.reset();
        m_window.reset();
    }

    virtual void draw( double deltatime ) = 0;

  protected:
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<QuadRenderer> m_quadRenderer;
    std::unique_ptr<WindowType> m_window;

    double m_lastTime{ 0 };

    void init( int width, int height ) {
        m_window       = std::make_unique<WindowType>( width, height );
        m_renderer     = std::make_unique<Renderer>( width, height );
        m_quadRenderer = std::make_unique<QuadRenderer>();
    }
};