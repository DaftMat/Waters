//
// Created by mathis on 31/05/2020.
//
#include <Core/Log.hpp>
#include "Primitives.hpp"

Mesh Primitives::plane(int resolution, float size) {
    HeightMap hmap(resolution);
    return plane(hmap, size);
}

Mesh Primitives::plane(const HeightMap &hmap, float size) {
    auto resolution = hmap.size();
    std::vector<Mesh::Vertex> vertices;
    std::vector<GLuint> indices;
    Mesh::Vertex vertex{};

    glm::vec3 axisA {size, 0.f, 0.f};
    glm::vec3 axisB {0.f, 0.f, size};

    for ( GLuint y = 0; y < resolution; ++y )
    {
        for ( GLuint x = 0; x < resolution; ++x )
        {
            /// Vertex
            GLuint index              = x + y * resolution;
            glm::vec2 percent         = glm::vec2( x, y ) / ( float(resolution) - 1.f );
            glm::vec3 point = glm::vec3 {0.f, hmap(x, y), 0.f} /// apply height map.
                            + ( percent.x - 0.5f ) * 2.f * axisA
                            + ( percent.y - 0.5f ) * 2.f * axisB;

            vertex.position = point;
            vertex.normal = glm::vec3{0.f};
            vertex.texCoords = percent;
            vertices.push_back( vertex );

            /// Triangles
            if ( x != resolution - 1 && y != resolution - 1 )
            {
                indices.push_back( index );
                indices.push_back( index + resolution + 1 );
                indices.push_back( index + resolution );

                indices.push_back( index );
                indices.push_back( index + 1 );
                indices.push_back( index + resolution + 1 );
            }
        }
    }

    ///set normals
    for (int y = 0 ; y < resolution ; ++y) {
        for (int x = 0 ; x < resolution ; ++x) {
            /// add neighbor triangles
            int index = x + y * resolution;
            std::vector<GLuint> inds{};
            if (x > 0 && y > 0) {
                inds.push_back(index - resolution - 1);
                inds.push_back(index);
                inds.push_back(index - 1);

                inds.push_back(index - resolution - 1);
                inds.push_back(index - resolution);
                inds.push_back(index);
            }
            if (y > 0 && x < resolution - 1) {
                inds.push_back(index - resolution);
                inds.push_back(index + 1);
                inds.push_back(index);
            }
            if (x > 0 && y < resolution - 1) {
                inds.push_back(index - 1);
                inds.push_back(index);
                inds.push_back(index + resolution);
            }
            if (x < resolution - 1 && y < resolution - 1) {
                inds.push_back(index);
                inds.push_back(index + 1);
                inds.push_back(index + resolution + 1);

                inds.push_back(index);
                inds.push_back(index + resolution + 1);
                inds.push_back(index + resolution);
            }

            /// calculate mean of all neighbor triangles' normals
            for (int i = 0; i < inds.size(); i += 3) {
                glm::vec<3, int> triangle{
                        inds[i],
                        inds[i + 1],
                        inds[i + 2]
                };
                if (triangle.x == index) {
                    auto a = glm::normalize(vertices[triangle.z].position - vertices[triangle.x].position);
                    auto b = glm::normalize(vertices[triangle.y].position - vertices[triangle.x].position);
                    auto triangleNormal = glm::normalize(glm::cross(a, b));
                    vertices[index].normal += triangleNormal;
                } else if (triangle.y == index) {
                    auto a = glm::normalize(vertices[triangle.x].position - vertices[triangle.y].position);
                    auto b = glm::normalize(vertices[triangle.z].position - vertices[triangle.y].position);
                    auto triangleNormal = glm::normalize(glm::cross(a, b));
                    vertices[index].normal += triangleNormal;
                } else if (triangle.z == index) {
                    auto a = glm::normalize(vertices[triangle.y].position - vertices[triangle.z].position);
                    auto b = glm::normalize(vertices[triangle.x].position - vertices[triangle.z].position);
                    auto triangleNormal = glm::normalize(glm::cross(a, b));
                    vertices[index].normal += triangleNormal;
                }
            }

            inds.clear();
            vertices[index].normal = glm::normalize(vertices[index].normal);
        }
    }

    return Loader::loadMesh(vertices, indices);
}