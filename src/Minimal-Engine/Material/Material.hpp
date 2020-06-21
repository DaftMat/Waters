//
// Created by mathis on 09/05/2020.
//
#pragma once

#include <vector>

#include "SettingManager.hpp"
#include "Texture.hpp"

class Material : public wtr::Core::NonCopyable {
   public:
    Material(Material &&) = default;
    Material &operator=(Material &&) = default;

    /** default constructor.
     *
     */
    Material() = default;

    /** preparation of the texture to be rendered.
     *
     */
    void prepare() const;

    /** Adds a texture to the material.
     *
     * @param name - name of the texture.
     * @param file - path of the texture.
     */
    void addTexture(Texture texture);

    /**
     * adds a bool setting to the material.
     * @tparam T - type of the setting's data.
     * @param name - name of the setting.
     * @param data - data of the setting.
     */
    template <typename T>
    void addSetting(std::string name, T data) {
        m_settings.add(std::move(name), data);
    }

    /** Deletes a texture from the material.
     *
     * @param name - name of the texture to be deleted.
     */
    void deleteTexture(const std::string &name);

    /**
     * Sets the bool data of a setting in the material.
     * @tparam T - type of the setting's data
     * @param name - name of the setting to be set.
     * @param data - new data of the setting.
     */
    template <typename T>
    void setSetting(std::string name, T data) {
        m_settings.set(std::move(name), data);
    }

    template <typename T>
    void deleteSetting(std::string name) {
        m_settings.remove<T>(std::move(name));
    }

    Texture &texture(const std::string &name);

    void reset();

    /** Textures list getter.
     *
     * @return list of textures in the material.
     */
    [[nodiscard]] const std::vector<Texture> &textures() const { return m_textures; }

    /** Settings list getter.
     *
     * @return list of settings in the material.
     */
    template <typename T>
    [[nodiscard]] const std::vector<SettingManager::Setting<T>> &settings() const {
        return m_settings.settings<T>();
    }

   private:
    std::vector<Texture> m_textures;
    SettingManager m_settings{};
};
