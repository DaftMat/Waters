//
// Created by mathis on 09/05/2020.
//

#include "Material.hpp"
#include <algorithm>

void Material::prepare() const {
    for ( int i = 0; i < m_textures.size(); ++i )
    {
        glActiveTexture( GL_TEXTURE0 + i );
        m_textures[i].bind();
    }
    glActiveTexture( GL_TEXTURE0 );
}

void Material::addTexture( Texture texture ) {
    m_textures.push_back( texture );
}

void Material::addSetting( std::string name, const glm::vec3& data ) {
    Setting setting{};
    setting.type            = Setting::Type::VECTOR;
    setting.name            = std::move( name );
    setting.data.vectorData = data;
    m_settings.push_back( setting );
}

void Material::addSetting( std::string name, float data ) {
    Setting setting{};
    setting.type            = Setting::Type::SCALAR;
    setting.name            = std::move( name );
    setting.data.scalarData = data;
    m_settings.push_back( setting );
}

void Material::addSetting( std::string name, bool data ) {
    Setting setting{};
    setting.type          = Setting::Type::BOOL;
    setting.name          = std::move( name );
    setting.data.boolData = data;
    m_settings.push_back( setting );
}

void Material::deleteTexture( const std::string& name ) {
    m_textures.erase(
        std::remove_if( m_textures.begin(),
                        m_textures.end(),
                        [name]( const Texture& texture ) { return texture.name() == name; } ),
        m_textures.end() );
}

void Material::deleteSetting( const std::string& name ) {
    m_settings.erase(
        std::remove_if( m_settings.begin(),
                        m_settings.end(),
                        [name]( const Setting& setting ) { return setting.name == name; } ),
        m_settings.end() );
}

void Material::setSetting( const std::string& name, const glm::vec3& data ) {
    std::find_if( m_settings.begin(), m_settings.end(), [name]( const Setting& setting ) {
        return setting.name == name;
    } )->data.vectorData = data;
}

void Material::setSetting( const std::string& name, float data ) {
    std::find_if( m_settings.begin(), m_settings.end(), [name]( const Setting& setting ) {
        return setting.name == name;
    } )->data.scalarData = data;
}

void Material::setSetting( const std::string& name, bool data ) {
    std::find_if( m_settings.begin(), m_settings.end(), [name]( const Setting& setting ) {
        return setting.name == name;
    } )->data.boolData = data;
}

Texture &Material::texture(const std::string &name) {
    return *std::find_if(m_textures.begin(), m_textures.end(), [name](const Texture &texture) {
        return texture.name() == name;
    });
}
