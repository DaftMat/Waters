//
// Created by mathis on 11/05/2020.
//

#ifndef DAFT_GAMEENGINE_POINTLIGHT_HPP
#define DAFT_GAMEENGINE_POINTLIGHT_HPP

#include "Light.hpp"

class PointLight : public Light {
   public:
    PointLight(const glm::vec3 &position, float intensity, const glm::vec3 &color = glm::vec3{1.f})
        : Light(color), m_position{position}, m_intensity{intensity} {}

    const glm::vec3 &position() const { return m_position; }

    glm::vec3 &position() { return m_position; }

    float intensity() const { return m_intensity; }

    float &intensity() { return m_intensity; }

   private:
    glm::vec3 m_position;
    float m_intensity;
};

#endif  // DAFT_GAMEENGINE_POINTLIGHT_HPP
