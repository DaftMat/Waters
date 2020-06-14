//
// Created by mathis on 07/06/2020.
//
#pragma once

#include <Minimal-Engine/Renderables/Renderable.hpp>
#include <array>

class Skybox : public Renderable {
   public:
    explicit Skybox(const std::string &skyDir, float size, float speed = 0.01f);
    ~Skybox() override = default;

    [[nodiscard]] float speed() const { return m_speed; }

    float &speed() { return m_speed; }

   private:
    std::array<std::string, 6> m_faces{"right", "left", "top", "bottom", "front", "back"};
    float m_speed;
};
