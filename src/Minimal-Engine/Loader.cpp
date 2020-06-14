//
// Created by mathis on 23/05/2020.
//
#define STB_IMAGE_IMPLEMENTATION

#include "Loader.hpp"

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <stb/stb_image.h>

#include <Core/Log.hpp>
#include <assimp/Importer.hpp>

Mesh Loader::loadMesh(const std::vector<Mesh::Vertex> &vertices, const std::vector<GLuint> &indices) {
    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Mesh::Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void *)nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void *)offsetof(Mesh::Vertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void *)offsetof(Mesh::Vertex, texCoords));

    glBindVertexArray(0);
    m_vaos.push_back(vao);
    m_vbos.push_back(vbo);
    m_vbos.push_back(ebo);
    return Mesh(vao, vbo, ebo, indices.size());
}

void Loader::clean() {
    for (auto &vao : m_vaos) glDeleteVertexArrays(1, &vao);
    for (auto &vbo : m_vbos) glDeleteBuffers(1, &vbo);
    for (auto &tex : m_texs) glDeleteTextures(1, &tex);
}

Texture Loader::loadTexture(const std::string &name, const std::string &path) {
    GLuint id;
    glGenTextures(1, &id);

    int width, height, numChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);
    if (data) {
        GLenum colorFormat;
        if (numChannels == 1)
            colorFormat = GL_RED;
        else if (numChannels == 3)
            colorFormat = GL_RGB;
        else if (numChannels == 4)
            colorFormat = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, id);

        glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        ENGINE_ERROR("Failed to load texture {0}", path);
    }
    stbi_image_free(data);
    m_texs.push_back(id);

    return Texture(name, id);
}

Texture Loader::loadCubeMap(const std::string &name, const std::array<std::string, 6> &paths) {
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);
    int width, height, numChannels;
    unsigned char *data;
    for (int i = 0; i < 6; ++i) {
        data = stbi_load(paths[i].c_str(), &width, &height, &numChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                         data);
            stbi_image_free(data);
        } else {
            ENGINE_ERROR("Failed to load texture {0}", paths[i]);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    m_texs.push_back(id);
    return Texture(name, id);
}

Mesh Loader::loadMesh(const std::string &filePath) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        ENGINE_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
    }

    aiMesh *mesh = scene->mMeshes[0];

    std::vector<Mesh::Vertex> vertices;
    std::vector<GLuint> indices;

    /// process vertices.
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Mesh::Vertex vertex{};
        glm::vec3 vector;
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
        // texture coordinates
        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec{0.f};
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        } else {
            vertex.texCoords = glm::vec2{0.f};
        }
        vertices.push_back(vertex);
    }
    /// process indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[(face.mNumIndices - 1) - j]);
    }

    return loadMesh(vertices, indices);
}

void Loader::deleteMesh(Mesh &mesh) {
    m_vaos.erase(std::remove(m_vaos.begin(), m_vaos.end(), mesh.vao()));
    m_vbos.erase(std::remove_if(m_vbos.begin(), m_vbos.end(),
                                [&mesh](GLuint elem) { return elem == mesh.vbo() || elem == mesh.ebo(); }),
                 m_vbos.end());
    glDeleteVertexArrays(1, &mesh.vao());
    glDeleteBuffers(1, &mesh.vbo());
    glDeleteBuffers(1, &mesh.ebo());
}

void Loader::deleteTexture(Texture &texture) {
    m_texs.erase(std::remove(m_texs.begin(), m_texs.end(), texture.id()));
    glDeleteTextures(1, &texture.id());
}

std::vector<GLuint> Loader::m_vaos{};
std::vector<GLuint> Loader::m_vbos{};
std::vector<GLuint> Loader::m_texs{};
