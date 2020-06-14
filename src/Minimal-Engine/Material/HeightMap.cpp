//
// Created by mathis on 16/05/2020.
//

#include "HeightMap.hpp"

HeightMap::HeightMap(const std::vector<float> &map, std::function<float(float)> fun)
    : m_map{map}, m_fun{std::move(fun)} {
    m_size = int(sqrt(double(map.size())));
}

HeightMap::HeightMap(int size, std::function<float(float)> fun) : m_size{int(size)}, m_fun{std::move(fun)} {
    m_map = std::vector<float>(m_size * m_size, 0.f);
}

glm::vec3 HeightMap::normal(int x, int y) const {
    float hL = m_fun(normalizedHeight(x - 1, y));
    float hR = m_fun(normalizedHeight(x + 1, y));
    float hD = m_fun(normalizedHeight(x, y - 1));
    float hU = m_fun(normalizedHeight(x, y + 1));

    return glm::normalize(glm::vec3{hL - hR, 1.f, hD - hU});
}

float HeightMap::operator()(int x, int y) const { return m_fun(normalizedHeight(x, y)); }

float HeightMap::normalizedHeight(int x, int y) const {
    if (x < 0) x = 0;
    if (x >= m_size) x = m_size - 1;
    if (y < 0) y = 0;
    if (y >= m_size) y = m_size - 1;
    return m_map[y * m_size + x];
}
