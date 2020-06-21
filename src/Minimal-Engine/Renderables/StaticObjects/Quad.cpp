//
// Created by mathis on 02/06/2020.
//
#include "Quad.hpp"

Quad::Quad(float x, float y, float width, float height) {
    std::vector<GLuint> indices{0, 1, 2, 0, 2, 3};
    std::vector<Mesh::Vertex> vertices;
    Mesh::Vertex vertex{};
    vertex.normal = glm::vec3{1.f, 1.f, 1.f};

    vertex.texCoords = glm::vec2(0.f, 1.f);
    vertex.position = glm::vec3(x, y, 0.f);
    vertices.push_back(vertex);
    vertex.texCoords = glm::vec2(1.f, 1.f);
    vertex.position = glm::vec3(x + width, y, 0.f);
    vertices.push_back(vertex);
    vertex.texCoords = glm::vec2(1.f, 0.f);
    vertex.position = glm::vec3(x + width, y - height, 0.f);
    vertices.push_back(vertex);
    vertex.texCoords = glm::vec2(0.f, 0.f);
    vertex.position = glm::vec3(x, y - height, 0.f);
    vertices.push_back(vertex);

    m_mesh = Mesh(std::move(vertices), std::move(indices));
    m_material.addTexture(Texture("quadTexture"));
}
