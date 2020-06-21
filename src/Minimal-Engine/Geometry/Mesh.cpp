//
// Created by mathis on 09/05/2020.
//

#include "Mesh.hpp"

#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <Core/Log.hpp>
#include <assimp/Importer.hpp>

void Mesh::prepare() const {
    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

void Mesh::render(GLuint type) const { glDrawElements(type, m_numVertex, GL_UNSIGNED_INT, nullptr); }

void Mesh::unbind() const {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void Mesh::reset() {
    if (isValid) {
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
        glDeleteVertexArrays(1, &m_vao);
        isValid = false;
    }
}

void Mesh::reset(std::vector<Vertex> vertices, std::vector<GLuint> indices) {
    m_numVertex = indices.size();
    int numVertices = vertices.size();
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Mesh::Vertex), std::move(vertices).data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numVertex * sizeof(GLuint), std::move(indices).data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void *)nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void *)offsetof(Mesh::Vertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void *)offsetof(Mesh::Vertex, texCoords));
    glBindVertexArray(0);
    isValid = true;
}

void Mesh::reset(std::string path) {
    Assimp::Importer importer;
    auto filePath = std::move(path);
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

    reset(std::move(vertices), std::move(indices));
}

Mesh &Mesh::operator=(Mesh &&other) noexcept {
    m_vao = other.m_vao;
    m_vbo = other.m_vbo;
    m_ebo = other.m_ebo;
    m_numVertex = other.m_numVertex;
    isValid = true;
    other.isValid = false;
    return *this;
}
