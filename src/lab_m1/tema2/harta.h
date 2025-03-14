#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include <vector>
#include <iostream>


namespace implemented {
    class Map {
    public:
        Map(int width, int height) : mapWidth(width), mapHeight(height) {
            CreateMap();
        }

        ~Map() {
            if (mapMesh) {
                delete mapMesh;
            }
        }

        void CreateMap() {
            vertices.clear();
            indices.clear();

            // Generate vertices
            for (int h = 0; h < mapHeight; h++) {
                for (int w = 0; w < mapWidth; w++) {
                    float x = w * gridSize - mapHeight/2;
                    float z = h * gridSize - mapWidth/2;
                    float y = 0.02f;  // Initial height

                    glm::vec3 position(x, y, z);
                    glm::vec3 normal(0, 1, 0);
                    glm::vec3 color(0.23f, 0.65f, 0.34f);

                    vertices.push_back(VertexFormat(position, color, normal));
                }
            }

            // Generate indices for triangles
            for (int h = 0; h < mapHeight - 1; h++) {
                for (int w = 0; w < mapWidth - 1; w++) {
                    // Get indices for current quad
                    unsigned int topLeft = h * mapWidth + w;
                    unsigned int topRight = topLeft + 1;
                    unsigned int bottomLeft = (h + 1) * mapWidth + w;
                    unsigned int bottomRight = bottomLeft + 1;

                    // First triangle (top-left, bottom-left, bottom-right)
                    indices.push_back(topLeft);
                    indices.push_back(bottomLeft);
                    indices.push_back(bottomRight);

                    // Second triangle (top-left, bottom-right, top-right)
                    indices.push_back(topLeft);
                    indices.push_back(bottomRight);
                    indices.push_back(topRight);
                }
            }

            // Create and initialize the mesh
            mapMesh = new Mesh("map");
            mapMesh->InitFromData(vertices, indices);
            mapMesh->SetDrawMode(GL_TRIANGLES);
        }

        void ModifyVertex(int x, int z, float newHeight) {
            if (x >= 0 && x < mapWidth && z >= 0 && z < mapHeight) {
                int index = z * mapWidth + x;
                vertices[index].position.y = newHeight;

                // Update the mesh with modified vertices
                mapMesh->InitFromData(vertices, indices);
            }
        }

        void ModifyVertexColor(int x, int z, glm::vec3 newColor) {
            if (x >= 0 && x < mapWidth && z >= 0 && z < mapHeight) {
                int index = z * mapWidth + x;
                vertices[index].color = newColor;

                // Update the mesh with modified vertices
                mapMesh->InitFromData(vertices, indices);
            }
        }

        glm::vec3 GetVertexPosition(int x, int z) {
            if (x >= 0 && x < mapWidth && z >= 0 && z < mapHeight) {
                int index = z * mapWidth + x;
                return vertices[index].position;
            }
            return glm::vec3(0);
        }

        Mesh* GetMesh() const {
            return mapMesh;
        }

        int GetWidth() const {
            return mapWidth;
        }

        int GetHeight() const {
            return mapHeight;
        }

    private:
        int mapWidth;
        int mapHeight;
        float gridSize = 1.0f;  // Size of each grid cell
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;
        Mesh* mapMesh = nullptr;
    };
}
