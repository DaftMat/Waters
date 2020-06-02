//
// Created by mathis on 09/05/2020.
//

#include "Camera.hpp"

Camera::Camera( const glm::vec3& position, const glm::vec3& worldUp, float yaw, float pitch ) :
    m_position{position},
    m_worldUp{worldUp},
    m_target{0.f},
    m_yaw{yaw},
    m_pitch{pitch},
    m_velocity{5.f},
    m_sensitivity{1.f},
    m_fov{45.f}{
    m_dist = glm::length(m_position - m_target);
    updateCameraVectors();
}

void Camera::processMovement( Camera::Movement movement, float dt ) {
    float ds = dt * m_velocity;
    switch ( movement ) {
        case FRONT:
            m_position += ds * m_front;
            m_target += ds * m_front;
            break;
        case BACK:
            m_position -= ds * m_front;
            m_target -= ds * m_front;
            break;
        case RIGHT:
            m_position += ds * m_right;
            m_target += ds * m_right;
            break;
        case LEFT:
            m_position -= ds * m_right;
            m_target -= ds * m_right;
            break;
        case UP:
            m_position += ds * m_worldUp;
            m_target += ds * m_worldUp;
            break;
        case DOWN:
            m_position -= ds * m_worldUp;
            m_target -= ds * m_worldUp;
            break;
    }
}

void Camera::processMouseScroll( float offset ) {
    m_dist -= offset * m_sensitivity;
    if (m_dist <= 0) m_dist = 0.001f;
    glm::vec3 dir = glm::normalize(m_position - m_target);
    m_position = m_target + m_dist * dir;
}

void Camera::updateCameraVectors() {
    m_front = glm::normalize(
        glm::vec3{glm::cos( glm::radians( m_yaw ) ) * glm::cos( glm::radians( m_pitch ) ),
                  glm::sin( glm::radians( m_pitch ) ),
                  glm::sin( glm::radians( m_yaw ) ) * glm::cos( glm::radians( m_pitch ) )} );
    m_right = glm::normalize( glm::cross( m_front, m_worldUp ) );
    m_up    = glm::normalize( glm::cross( m_right, m_front ) );
}

void Camera::processMouseMove(const glm::vec2 &mousePos) {
    if (!m_mousePressed) return;
    if (m_firstMouseMove) {
        m_mousePosition = mousePos;
        m_firstMouseMove = false;
    }
    auto mouseOffset = mousePos - m_mousePosition;
    m_mousePosition = mousePos;
    ///pitch and yaw
    m_yaw += mouseOffset.x * m_sensitivity * 0.1f;
    m_pitch -= mouseOffset.y * m_sensitivity * 0.1f;
    if (m_pitch > 89.f) m_pitch = 89.f;
    if (m_pitch < -89.f) m_pitch = -89.f;
    ///position
    float hDist = m_dist * glm::cos(glm::radians(m_pitch));
    float vDist = m_dist * glm::sin(glm::radians(m_pitch));
    float xoffset = hDist * glm::cos(glm::radians(m_yaw));
    float zoffset = hDist * glm::sin(glm::radians(m_yaw));
    m_position = glm::vec3 {
        m_target.x - xoffset,
        m_target.y - vDist,
        m_target.z - zoffset
    };
    updateCameraVectors();
}
