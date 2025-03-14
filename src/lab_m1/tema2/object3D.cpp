#include "object3D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"
#include <iostream>
using namespace std;


Mesh* object3D::CreateCube(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;
    std::vector<VertexFormat> vertices = {
        // Front face
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color),
        // Back face
        VertexFormat(corner + glm::vec3(0, 0, length), color),
        VertexFormat(corner + glm::vec3(length, 0, length), color),
        VertexFormat(corner + glm::vec3(length, length, length), color),
        VertexFormat(corner + glm::vec3(0, length, length), color)
    };

    std::vector<unsigned int> indices;
    if (fill) {
        indices = {
            // Front face
            0, 1, 2,
            0, 2, 3,
            // Back face
            4, 5, 6,
            4, 6, 7,
            // Top face
            3, 2, 6,
            3, 6, 7,
            // Bottom face
            0, 1, 5,
            0, 5, 4,
            // Right face
            1, 2, 6,
            1, 6, 5,
            // Left face
            0, 3, 7,
            0, 7, 4
        };
    }
    else {
        indices = {
            // Front face
            0, 1, 1, 2, 2, 3, 3, 0,
            // Back face
            4, 5, 5, 6, 6, 7, 7, 4,
            // Connecting edges
            0, 4, 1, 5, 2, 6, 3, 7
        };
    }

    Mesh* cube = new Mesh(name);
    cube->SetDrawMode(fill ? GL_TRIANGLES : GL_LINES);
    cube->InitFromData(vertices, indices);
    return cube;
}

Mesh* object3D::CreateCilinder(
    const std::string& name,
    glm::vec3 center,
    float radius,
    float height,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    const int numSegments = 32;

    // Generate circle vertices for top and bottom
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * M_PI * i / numSegments;
        float x = radius * cos(theta);
        float z = radius * sin(theta);

        // Bottom circle
        vertices.push_back(VertexFormat(center + glm::vec3(x, 0, z), color));
        // Top circle
        vertices.push_back(VertexFormat(center + glm::vec3(x, height, z), color));
    }

    if (fill) {
        // Generate indices for the sides
        for (int i = 0; i < numSegments; i++) {
            int next = (i + 1) % numSegments;
            indices.push_back(2 * i);
            indices.push_back(2 * i + 1);
            indices.push_back(2 * next);
            indices.push_back(2 * next);
            indices.push_back(2 * i + 1);
            indices.push_back(2 * next + 1);
        }
    }
    else {
        // Create outline
        for (int i = 0; i < numSegments; i++) {
            indices.push_back(2 * i);
            indices.push_back(2 * ((i + 1) % numSegments));
            indices.push_back(2 * i + 1);
            indices.push_back(2 * ((i + 1) % numSegments) + 1);
        }
    }

    Mesh* cylinder = new Mesh(name);
    cylinder->SetDrawMode(fill ? GL_TRIANGLES : GL_LINES);
    cylinder->InitFromData(vertices, indices);
    return cylinder;
}

Mesh* object3D::CreateCone(
    const std::string& name,
    glm::vec3 center,
    float radius,
    float height,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    const int numSegments = 32;

    // Add apex vertex
    vertices.push_back(VertexFormat(center + glm::vec3(0, height, 0), color));

    // Generate base circle vertices
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * M_PI * i / numSegments;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        vertices.push_back(VertexFormat(center + glm::vec3(x, 0, z), color));
    }

    if (fill) {
        // Generate triangles
        for (int i = 1; i < numSegments; i++) {
            indices.push_back(0);  // apex
            indices.push_back(i);
            indices.push_back(i + 1);
        }
        // Close the cone
        indices.push_back(0);
        indices.push_back(numSegments);
        indices.push_back(1);
    }
    else {
        // Create outline
        for (int i = 1; i <= numSegments; i++) {
            indices.push_back(i);
            indices.push_back((i % numSegments) + 1);
            indices.push_back(0);  // apex
            indices.push_back(i);
        }
    }

    Mesh* cone = new Mesh(name);
    cone->SetDrawMode(fill ? GL_TRIANGLES : GL_LINES);
    cone->InitFromData(vertices, indices);
    return cone;
}

Mesh* object3D::CreateSphere(
    const std::string& name,
    glm::vec3 center,
    float radius,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    const int stacks = 16;
    const int sectors = 32;

    // Generate vertices
    for (int i = 0; i <= stacks; i++) {
        float phi = M_PI * i / stacks;
        for (int j = 0; j <= sectors; j++) {
            float theta = 2 * M_PI * j / sectors;
            float x = radius * sin(phi) * cos(theta);
            float y = radius * cos(phi);
            float z = radius * sin(phi) * sin(theta);
            vertices.push_back(VertexFormat(center + glm::vec3(x, y, z), color));
        }
    }

    if (fill) {
        // Generate triangles
        for (int i = 0; i < stacks; i++) {
            for (int j = 0; j < sectors; j++) {
                int first = i * (sectors + 1) + j;
                int second = first + sectors + 1;
                indices.push_back(first);
                indices.push_back(second);
                indices.push_back(first + 1);
                indices.push_back(second);
                indices.push_back(second + 1);
                indices.push_back(first + 1);
            }
        }
    }
    else {
        // Create outline
        for (int i = 0; i < stacks; i++) {
            for (int j = 0; j < sectors; j++) {
                int first = i * (sectors + 1) + j;
                indices.push_back(first);
                indices.push_back(first + 1);
                indices.push_back(first);
                indices.push_back(first + sectors + 1);
            }
        }
    }

    Mesh* sphere = new Mesh(name);
    sphere->SetDrawMode(fill ? GL_TRIANGLES : GL_LINES);
    sphere->InitFromData(vertices, indices);
    return sphere;
}

Mesh* object3D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}