//
// Created by mathis on 15/06/2020.
//
#pragma once

#include <Core/NonCopyable.hpp>
#include <Core/OpenGL.hpp>
#include <string>

class SettingManager : public wtr::Core::NonCopyable {
   public:
    /** non-texture material settings.
     * e.g. albedo color, procedural textures, ...
     */
    template <typename T>
    struct Setting : public wtr::Core::NonCopyable {
        explicit Setting(std::string pname) : name(std::move(pname)) {}
        Setting(std::string pname, T pdata) : name(std::move(pname)), data{pdata} {}

        Setting(Setting<T> &&) noexcept = default;
        Setting &operator=(Setting<T> &&) noexcept = default;

        bool operator==(Setting<T> &&o) const noexcept { return name == o.name; }
        bool operator==(const Setting<T> &o) const noexcept { return name == o.name; }

        std::string name;
        T data;  ///< data of the settings.
    };

    using intSetting = Setting<int>;
    using boolSetting = Setting<bool>;
    using floatSetting = Setting<float>;
    using vec2Setting = Setting<glm::vec2>;
    using vec3Setting = Setting<glm::vec3>;
    using vec4Setting = Setting<glm::vec4>;
    using mat2Setting = Setting<glm::mat2>;
    using mat3Setting = Setting<glm::mat3>;
    using mat4Setting = Setting<glm::mat4>;

    SettingManager() noexcept = default;

    SettingManager(SettingManager &&) noexcept = default;
    SettingManager &operator=(SettingManager &&) noexcept = default;

    template <typename T>
    inline const std::vector<SettingManager::Setting<T>> &settings() const;

    template <typename T>
    inline std::vector<SettingManager::Setting<T>> &settings();

    template <typename T>
    inline void add(std::string name, T value) noexcept;

    template <typename T>
    inline void set(std::string name, T value) {
        get<T>(std::move(name)) = value;
    }

    template <typename T>
    inline void remove(std::string name) {
        std::remove(getIt<T>(std::move(name)));
    }

    void clear() noexcept;

   private:
    template <typename T>
    inline auto getIt(std::string name) const;

    template <typename T>
    inline auto getIt(std::string name);

    template <typename T>
    inline const T &get(std::string name) const {
        return getIt<T>(std::move(name))->data;
    }

    template <typename T>
    inline T &get(std::string name);

    std::vector<intSetting> m_ints;
    std::vector<boolSetting> m_bools;
    std::vector<floatSetting> m_floats;
    std::vector<vec2Setting> m_vec2s;
    std::vector<vec3Setting> m_vec3s;
    std::vector<vec4Setting> m_vec4s;
    std::vector<mat2Setting> m_mat2s;
    std::vector<mat3Setting> m_mat3s;
    std::vector<mat4Setting> m_mat4s;
};

#include <Minimal-Engine/Material/SettingManager.inl>