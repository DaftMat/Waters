//
// Created by mathis on 23/05/2020.
//
#pragma once
#include <API.hpp>

#include <Minimal-Engine/Geometry/Mesh.hpp>
#include <Minimal-Engine/Material/Texture.hpp>
#include <spdlog/common.h>

class ENGINE_API Loader
{
  public:
    static Mesh loadMesh( const std::vector<Mesh::Vertex>& vertices,
                          const std::vector<GLuint>& indices );
    static Mesh loadMesh( const std::string &filePath);
    static Texture loadTexture( const std::string& name, const std::string& path );
    static void clean();

  private:
    static std::vector<GLuint> m_vaos;
    static std::vector<GLuint> m_vbos;
    static std::vector<GLuint> m_texs;
};
