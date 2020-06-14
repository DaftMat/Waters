//
// Created by mathis on 13/05/2020.
//

#ifndef DAFT_GAMEENGINE_LIGHT_HPP
#define DAFT_GAMEENGINE_LIGHT_HPP

#include <Core/OpenGL.hpp>

class Light {
   public:
    explicit Light(const glm::vec3 &color = glm::vec3{1.f}) : m_color{color} {}

    const glm::vec3 &color() const { return m_color; }

    glm::vec3 &color() { return m_color; }

   private:
    glm::vec3 m_color;
};

#endif  // DAFT_GAMEENGINE_LIGHT_HPP
