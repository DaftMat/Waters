//
// Created by mathis on 07/06/2020.
//
#pragma once


#include <Minimal-Engine/Renderables/StaticObjects/Object.hpp>

class Player : public Object {
public:
    enum Movement {
        FRONT, BACK, RIGHT, LEFT
    };

    explicit Player( const Mesh &mesh,
            const glm::vec3 &position = glm::vec3 {0.f},
            const glm::vec3 &rotation = glm::vec3 {0},
            const glm::vec3 &scale = glm::vec3 {1.f}) : Object(mesh, position, rotation, scale) {}

    void processMovement(Movement movement, float dt);

    void jump();

    void update(float dt, float height);

private:
    float m_velocity{5.f};
    float m_turnspeed{120.f};
    float m_jumpforce{7.5f};
    float m_currentJumpForce{0.f};
    bool m_jumping{false};
    static const float m_gravity;
};
