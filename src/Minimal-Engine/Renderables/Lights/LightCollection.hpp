//
// Created by mathis on 13/05/2020.
//

#ifndef DAFT_GAMEENGINE_LIGHTCOLLECTION_HPP
#define DAFT_GAMEENGINE_LIGHTCOLLECTION_HPP

#include <vector>

#include "DirectLight.hpp"
#include "PointLight.hpp"

/** A class that wraps all types of Light together.
 *
 */
class LightCollection {
   public:
    LightCollection() = default;

    void addLight(const PointLight &light) { m_pointLights.push_back(light); }

    void addLight(const DirectLight &light) { m_directLights.push_back(light); }

    const std::vector<PointLight> &pointLights() const { return m_pointLights; }

    std::vector<PointLight> &pointLights() { return m_pointLights; }

    const std::vector<DirectLight> &directLights() const { return m_directLights; }

    std::vector<DirectLight> &directLights() { return m_directLights; }

   private:
    std::vector<PointLight> m_pointLights;
    std::vector<DirectLight> m_directLights;
};

#endif  // DAFT_GAMEENGINE_LIGHTCOLLECTION_HPP
