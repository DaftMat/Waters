//
// Created by mathis on 31/05/2020.
//
#pragma once


#include <Minimal-Engine/Renderables/Renderable.hpp>
#include <Minimal-Engine/Material/HeightMap.hpp>

/** Class for terrain objects.
 *
 */
class ENGINE_API Terrain : public Renderable {
public:
    /** Plane terrain constructor.
     *
     * @param resolution - number of vertices on the terrain's border.
     * @param size - size of the terrain in the world.
     */
    explicit Terrain(int resolution, float size = 10.f);

    /** Constructor for terrain with height map.
     *
     * @param hmap - terrain's height map - see HeightMap .
     * @param size - size of the terrain in the world.
     */
    explicit Terrain(const HeightMap &hmap, float size = 10.f);

    [[nodiscard]] glm::mat4 model() const override { return glm::translate(glm::mat4{1.f}, m_position); }

private:
    void init(float size);

    glm::vec3 m_position{0.f};
};
