//
// Created by mathis on 16/05/2020.
//

#ifndef DAFT_GAMEENGINE_HEIGHTMAP_HPP
#define DAFT_GAMEENGINE_HEIGHTMAP_HPP

#include <API.hpp>

#include <Minimal-Engine/Material/PerlinNoise/Perlin.hpp>
#include <functional>
#include <vector>

class ENGINE_API HeightMap
{
  public:
    explicit HeightMap(
        const std::vector<float>& map,
        std::function<float( float )> fun = []( float h ) { return h; } );

    /** Constructor filling the hmap with 0s.
     *
     * @param size - size of the hmap
     */
    explicit HeightMap(
        int size,
        std::function<float( float )> fun = []( float h ) { return h; } );

    float operator()( int x, int y ) const;

    [[nodiscard]] glm::vec3 normal( int x, int y ) const;

    [[nodiscard]] float normalizedHeight( int x, int y ) const;

    [[nodiscard]] int size() const { return m_size; }

    void setFun( std::function<float( float )> curve ) { m_fun = std::move( curve ); }

    [[nodiscard]] auto getFun() const { return m_fun; }

    [[nodiscard]] std::vector<float> getMap() const { return m_map; }

    void reset() { m_map.clear(); }

    void reset(const std::vector<float> map) { m_map = map; }

  private:
    std::vector<float> m_map;
    int m_size;
    std::function<float( float )> m_fun;
};

#endif // DAFT_GAMEENGINE_HEIGHTMAP_HPP
