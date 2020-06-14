//
// Created by mathis on 07/06/2020.
//
#include "Player.hpp"

void Player::processMovement(Player::Movement movement, float dt) {
    float ds = dt * m_velocity;
    float dr = dt * m_turnspeed;

    float theta = glm::radians(getRotation().y);
    glm::vec3 pos = glm::vec3{0};
    switch (movement) {
        case FRONT:
            pos.x = ds * glm::sin(theta);
            pos.z = ds * glm::cos(theta);
            translate(pos);
            break;
        case BACK:
            pos.x = -ds * glm::sin(theta);
            pos.z = -ds * glm::cos(theta);
            translate(pos);
            break;
        case RIGHT:
            rotate(glm::vec3{0.f, -dr, 0.f});
            break;
        case LEFT:
            rotate(glm::vec3{0.f, dr, 0.f});
            break;
    }
}

void Player::update(float dt, float height) {
    glm::vec3 pos{0.f};
    m_currentJumpForce += m_gravity * dt;
    pos.y = m_currentJumpForce * dt;
    translate(pos);
    if (getPosition().y < height) {
        m_currentJumpForce = 0.f;
        pos = getPosition();
        pos.y = height;
        setPosition(pos);
        m_jumping = false;
    }
}

const float Player::m_gravity{-13.81};

void Player::jump() {
    if (!m_jumping) {
        m_currentJumpForce = m_jumpforce;
        m_jumping = true;
    }
}
