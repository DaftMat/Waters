//
// Created by mathis on 02/06/2020.
//
#pragma once

#include <Minimal-Engine/Renderables/Renderable.hpp>

class Water : public Renderable
{
  public:
    explicit Water( float speed = 0.03f, int resolution = 128, float size = 10.f );

    void move( double deltatime );

    [[nodiscard]] glm::mat4 model() const override {
        return glm::translate( glm::mat4{ 1.f }, m_position );
    }

    [[nodiscard]] const glm::vec3& position() const { return m_position; }

    [[nodiscard]] glm::vec3& position() { return m_position; }

  private:
    float m_speed;
    float m_offset{ 0 };

    glm::vec3 m_position{ 0.f };
};
