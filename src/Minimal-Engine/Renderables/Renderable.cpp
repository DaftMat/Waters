//
// Created by mathis on 31/05/2020.
//
#include "Renderable.hpp"

void Renderable::prepare() const {
    m_mesh.prepare();
    m_material.prepare();
}

void Renderable::render( GLuint type ) const {
    m_mesh.render( type );
}

void Renderable::unbind() const {
    m_mesh.unbind();
}
