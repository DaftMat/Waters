//
// Created by mathis on 09/05/2020.
//

#ifndef DAFT_GAMEENGINE_OBJECT_HPP
#define DAFT_GAMEENGINE_OBJECT_HPP

#include <Minimal-Engine/Renderables/Renderable.hpp>

/** MeshObject Entity.
 * MeshObject with transformation matrix.
 */
class Object : public Renderable
{
  public:
    /** Constructor.
     *
     * @param meshObject - wrapped MeshObject.
     * @param pos - object position.
     * @param rot - object rotations.
     * @param scale - object scale.
     */
    explicit Object( const Mesh &mesh,
                     const glm::vec3& pos   = glm::vec3{ 0.f },
                     const glm::vec3& rot   = glm::vec3{ 0.f },
                     const glm::vec3& scale = glm::vec3{ 1.f } );

    /** Transformation matrix.
     *
     * @return object's transformation matrix.
     */
    [[nodiscard]] glm::mat4 model() const override { return translation() * rotation() * scale(); }

    /** Translates the object.
     *
     * @param t - direction to "add" to the object.
     */
    void translate( const glm::vec3& t ) { m_position += t; }

    /** Rotates the object.
     *
     * @param r - rotation to "add" to the object.
     */
    void rotate( const glm::vec3& r ) { m_rotation += r; }

    /** Position getter.
     *
     * @return object position.
     */
    [[nodiscard]] const glm::vec3& getPosition() const { return m_position; }

    /** Position setter.
     *
     * @param pos - new position.
     */
    void setPosition( const glm::vec3& pos ) { m_position = pos; }

    /** Rotation getter.
     *
     * @return object rotation.
     */
    [[nodiscard]] const glm::vec3& getRotation() const { return m_rotation; }

    /** Rotation setter.
     *
     * @param rot - new rotation.
     */
    void setRotation( const glm::vec3& rot ) { m_rotation = rot; }

    /** Scale getter.
     *
     * @return object scale.
     */
    [[nodiscard]] const glm::vec3& getScale() const { return m_scale; }

    /** Scale setter.
     *
     * @param scale - new scale.
     */
    void setScale( const glm::vec3& scale ) { m_scale = scale; }

    void addAlbedoTexture(const std::string &texPath);

    void addSpecularTexture(const std::string &texPath);

  private:
    [[nodiscard]] glm::mat4 translation() const { return glm::translate( glm::mat4{ 1.f }, m_position ); };
    [[nodiscard]] glm::mat4 rotation() const;
    [[nodiscard]] glm::mat4 scale() const { return glm::scale( glm::mat4{ 1.f }, m_scale ); };

    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};

#endif // DAFT_GAMEENGINE_OBJECT_HPP
