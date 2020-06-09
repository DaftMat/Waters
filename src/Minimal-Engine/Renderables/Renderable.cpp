//
// Created by mathis on 31/05/2020.
//
#include <Minimal-Engine/Loader.hpp>
#include "Renderable.hpp"

void Renderable::prepare() const {
    if (!m_visible) return;
    m_mesh.prepare();
    m_material.prepare();
}

void Renderable::render( GLuint type ) const {
    if (!m_visible) return;
    m_mesh.render( type );
}

void Renderable::unbind() const {
    if (!m_visible) return;
    m_mesh.unbind();
}

void Renderable::toggleVisible() {
    m_visible = !m_visible;
    if (!m_visible) {
        Loader::deleteMesh(m_mesh);
        m_material.reset();
    } else {
        m_mesh = generateMesh();
    }
    //set material (in inherited classes)
}
