//
// Created by mathis on 31/05/2020.
//
#pragma once

#include <Minimal-Engine/Geometry/Primitives.hpp>
#include <Minimal-Engine/Material/HeightMap.hpp>
#include <Minimal-Engine/Renderables/Renderable.hpp>

/** Class for terrain objects.
 *
 */
class ENGINE_API Terrain : public Renderable {
   public:
    struct TextureLayer {
        TextureLayer(std::string cpath, float cstartHeight, float cblend)
            : path{std::move(cpath)}, startHeight{cstartHeight}, blend{cblend} {}

        std::string path;
        float startHeight;
        float blend;
    };
    /** Plane terrain constructor.
     *
     * @param resolution - number of vertices on the terrain's border.
     * @param size - size of the terrain in the world.
     */
    explicit Terrain(int resolution = 128, float size = 10.f);

    /** Constructor for terrain with height map.
     *
     * @param hmap - terrain's height map - see HeightMap .
     * @param size - size of the terrain in the world.
     */
    explicit Terrain(const HeightMap &hmap, float size = 10.f, int lod = 0);

    [[nodiscard]] glm::mat4 model() const override { return glm::translate(glm::mat4{1.f}, m_position); }

    [[nodiscard]] glm::vec3 &position() { return m_position; }

    [[nodiscard]] const glm::vec3 &position() const { return m_position; }

    void addTextureLayer(const TextureLayer &textureLayer);

    [[nodiscard]] float getHeight(float x, float y) const;

    void setLod(int lod);

    void toggleVisible() override;

   private:
    Mesh generateMesh() override { return Primitives::plane(m_hmap, m_size, m_lod); }

    void init(float size);
    [[nodiscard]] static float barerp(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3,
                                      const glm::vec2 &pos);
    [[nodiscard]] static float mod(float a, float b);

    glm::vec3 m_position{0.f};
    int m_numLayers{0};
    float m_minHeight, m_maxHeight;
    HeightMap m_hmap;  // for physics
    float m_size;
    int m_resolution;
    int m_lod;
};
