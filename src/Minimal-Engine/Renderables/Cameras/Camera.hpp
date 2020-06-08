//
// Created by mathis on 09/05/2020.
//

#ifndef DAFT_GAMEENGINE_CAMERA_HPP
#define DAFT_GAMEENGINE_CAMERA_HPP
#include <API.hpp>

#include <Core/OpenGL.hpp>

/** camera class.
 * camera giving the view matrix.
 */
class ENGINE_API Camera
{
  public:

    /** Constructor.
     * no roll as this camera won't need it.
     * @param position - position of the camera
     * @param worldUp - upward direction of the camera
     * @param yaw - horizontal rotation
     * @param pitch - vertical rotation
     */
    explicit Camera( const glm::vec3& position = { 0.f, 0.f, -3.f },
                     const glm::vec3& worldUp  = { 0.f, 1.f, 0.f },
                     float yaw                 = 90.f,
                     float pitch               = 0.f );

    /** calculates view matrix.
     *
     * @return the view matrix of the camera.
     */
    [[nodiscard]] glm::mat4 getViewMatrix() const {
        return glm::lookAt( m_position, m_position + m_front, m_up );
    }

    /** fov getter.
     *
     * @return fov (zoom) of the camera.
     */
    [[nodiscard]] float getFov() const { return m_fov; }

    /** position getter.
     *
     * @return position of the camera.
     */
    [[nodiscard]] glm::vec3 getPosition() const { return m_position; }

    /** position setter.
     *
     * @param newPos - new position of the camera
     */
    void setPosition( const glm::vec3& newPos ) { m_position = newPos; }

    void translate( const glm::vec3& t ) { m_position += t; }

    /** front getter.
     *
     * @return the direction the camera faces.
     */
    [[nodiscard]] glm::vec3 getViewDirection() const { return m_front; }

    /** mouse scroll movement processing function.
     * will move forward or backward (with the limit of .
     * @param offset - difference between last position and current position of the scroll
     */
    void processMouseScroll( float offset );

    void processMousePress( const glm::vec2& mousePos ) {
        m_mousePressed  = true;
        m_mousePosition = mousePos;
    }

    void processMouseRelease() { m_mousePressed = false; }

    /** mouse movement processing function.
     *
     * @param mousePos - current mouse position.
     */
    void processMouseMove( const glm::vec2& mousePos );

    void flip();

    void update(const glm::vec3 &targetPos, float rot);

    void updateYaw(float dt);

  private:
    void updateCameraVectors();
    void updatePosition();

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;
    glm::vec3 m_target;

    float m_baseYaw, m_yaw, m_pitch, m_rot, m_dist;
    float m_velocity, m_sensitivity, m_fov;

    glm::vec2 m_mousePosition;
    bool m_mousePressed{ false };
};

#endif // DAFT_GAMEENGINE_CAMERA_HPP
