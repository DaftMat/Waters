//
// Created by mathis on 13/05/2020.
//

#ifndef DAFT_GAMEENGINE_DIRECTLIGHT_HPP
#define DAFT_GAMEENGINE_DIRECTLIGHT_HPP

#include "Light.hpp"

class DirectLight : public Light {
   public:
    explicit DirectLight(const glm::vec3 &direction, const glm::vec3 &color = glm::vec3{1.f})
        : Light(color), m_direction{direction} {}

    const glm::vec3 &direction() const { return m_direction; }

    glm::vec3 &direction() { return m_direction; }

   private:
    glm::vec3 m_direction;
};

#endif  // DAFT_GAMEENGINE_DIRECTLIGHT_HPP
