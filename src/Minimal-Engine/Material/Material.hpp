//
// Created by mathis on 09/05/2020.
//

#ifndef DAFT_GAMEENGINE_MATERIAL_HPP
#define DAFT_GAMEENGINE_MATERIAL_HPP

#include "Texture.hpp"
#include <vector>

class Material
{
  public:
    /** non-texture material settings.
     * e.g. albedo color, procedural textures, ...
     */
    struct Setting {
        enum Type { VECTOR, SCALAR, BOOL, INT } type;
        std::string name; ///< name of the setting.
        union {
            glm::vec3 vectorData;
            float scalarData;
            int intData;
            bool boolData;
        } data; ///< data of the settings, can either be a vector or a float.
    };

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
    void addTexture( Texture texture );

    /** Adds a vector setting to the material.
     *
     * @param name - name of the setting.
     * @param data - vector of the setting.
     */
    void addSetting( std::string name, const glm::vec3& data );

    /** Adds a float setting to the material.
     *
     * @param name - name of the setting.
     * @param data - float of the setting.
     */
    void addSetting( std::string name, float data );

    /** adds a bool setting to the material.
     *
     * @param name - name of the setting.
     * @param data - bool of the setting.
     */
    void addSetting( std::string name, bool data );

    /** adds a bool setting to the material.
     *
     * @param name - name of the setting.
     * @param data - bool of the setting.
     */
    void addSetting( std::string name, int data );

    /** Deletes a texture from the material.
     *
     * @param name - name of the texture to be deleted.
     */
    void deleteTexture( const std::string& name );

    /** Deletes a setting from the material.
     *
     * @param name - name of the setting to be deleted.
     */
    void deleteSetting( const std::string& name );

    /** Sets the vector data of a setting in the material.
     *
     * @param name - name of the setting to be set.
     * @param data - new vector of the setting.
     */
    void setSetting( const std::string& name, const glm::vec3& data );

    /** Sets the float data of a setting in the material.
     *
     * @param name - name of the setting to be set.
     * @param data - new float of the setting.
     */
    void setSetting( const std::string& name, float data );

    /** Sets the bool data of a setting in the material.
     *
     * @param name - name of the setting to be set.
     * @param data - new bool of the setting.
     */
    void setSetting( const std::string& name, bool data );

    /** Sets the bool data of a setting in the material.
     *
     * @param name - name of the setting to be set.
     * @param data - new bool of the setting.
     */
    void setSetting( const std::string& name, int data );

    Texture& texture( const std::string& name );

    /** Textures list getter.
     *
     * @return list of textures in the material.
     */
    const std::vector<Texture>& textures() const { return m_textures; }

    /** Settings list getter.
     *
     * @return list of settings in the material.
     */
    const std::vector<Setting>& settings() const { return m_settings; }

  private:
    std::vector<Texture> m_textures;
    std::vector<Setting> m_settings;
};

#endif // DAFT_GAMEENGINE_MATERIAL_HPP
