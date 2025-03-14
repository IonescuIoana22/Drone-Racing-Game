#pragma once
#include "utils/glm_utils.h"
#include "utils/math_utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "object3D.h"
#include <vector>
#include <random>
#include <iostream>

using namespace std;

namespace implemented
{
    class Checkpoint {
    public:
        Checkpoint() {}
        ~Checkpoint() {}

		glm::vec3 position;

        void CreateCheckpoint(vector<vector<int>>& pozitiiObiecte, int halfMap, int Random, vector< implemented::Drona::BoundingBox*>& coliziuni_obiecte) {
            {
                meshes.clear();
                // Create checkpoint frame (square) with white color
                Mesh* mesh = object3D::CreateCube("frame", glm::vec3(-0.5f, 0, -0.5f), 1.0f, glm::vec3(1), false); // White wireframe
                meshes.push_back(mesh);

                // Create left support pole with green color
                mesh = object3D::CreateCube("leftPole", glm::vec3(-0.5f, 0, -0.5f), 1.0f, glm::vec3(0, 1, 0), true); // Solid green
                meshes.push_back(mesh);

                // Create right support pole with green color
                mesh = object3D::CreateCube("rightPole", glm::vec3(-0.5f, 0, -0.5f), 1.0f, glm::vec3(0, 1, 0), true); // Solid green
                meshes.push_back(mesh);
            }

            {
                transforms.clear();
                coliziuni_obiecte.clear();
                glm::mat4 modelMatrix;

                // Random position generation
                random_device rd;
                mt19937 generator(rd());
                uniform_int_distribution<int> distribution(-Random, Random);

                int x, z;
                do {
                    x = distribution(generator);
                    z = distribution(generator);
                } while (pozitiiObiecte[x + halfMap][z + halfMap] == 1 ||
                    pozitiiObiecte[x + halfMap][z + halfMap + 1] == 1 || pozitiiObiecte[x + halfMap][z + halfMap + 2] == 1 ||
                    pozitiiObiecte[x + halfMap][z + halfMap - 1] == 1 || pozitiiObiecte[x + halfMap][z + halfMap - 2] == 1); // Avoid center area

                pozitiiObiecte[x + halfMap][z + halfMap] = 1;
                pozitiiObiecte[x + halfMap][z + halfMap + 1] = 1;
                pozitiiObiecte[x + halfMap][z + halfMap + 2] = 1;
                pozitiiObiecte[x + halfMap][z + halfMap - 1] = 1;
                pozitiiObiecte[x + halfMap][z + halfMap - 2] = 1;

                position = glm::vec3(x, 0, z); // Store position for collision detection
                glm::vec3 min = glm::vec3(-0.5, 0, -0.5);
                glm::vec3 max = glm::vec3(0.5, 1, 0.5);

                // Constants for dimensions
                const float frameSize = 3.6f;     // Size of the square frame
                const float frameThickness = 0.05f; // Thickness of the frame
                const float poleHeight = 4.0f;     // Height of support poles
                const float poleThickness = 0.1f;  // Thickness of support poles
                const float frameHeight = 3.0f;    // Height of the frame from ground

                // Transform for checkpoint frame - scale and position
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position + glm::vec3(0, frameHeight, 0));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(frameSize, frameThickness, 2));
                transforms.push_back(modelMatrix);

                // Transform for left support pole
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position + glm::vec3(-frameSize / 2, 0, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(poleThickness, poleHeight, poleThickness));
                transforms.push_back(modelMatrix);

                glm::vec3 mmin = glm::vec3(modelMatrix * glm::vec4(min, 1));
                glm::vec3 mmax = glm::vec3(modelMatrix * glm::vec4(max, 1));
                implemented::Drona::BoundingBox* obiect = new implemented::Drona::BoundingBox;
                obiect->minPoint = mmin;
                obiect->maxPoint = mmax;
                coliziuni_obiecte.push_back(obiect);

                // Transform for right support pole
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position + glm::vec3(frameSize / 2, 0, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(poleThickness, poleHeight, poleThickness));
                transforms.push_back(modelMatrix);

                mmin = glm::vec3(modelMatrix * glm::vec4(min, 1));
                mmax = glm::vec3(modelMatrix * glm::vec4(max, 1));
                obiect = new implemented::Drona::BoundingBox;
                obiect->minPoint = mmin;
                obiect->maxPoint = mmax;
                coliziuni_obiecte.push_back(obiect);
            }
        }

        void ChangeMesh(glm::vec3 culoare) {
            {
                meshes.clear();
                // Create checkpoint frame (square) with white color
                Mesh* mesh = object3D::CreateCube("frame", glm::vec3(-0.5f, 0, -0.5f), 1.0f, culoare, false); // White wireframe
                meshes.push_back(mesh);

                // Create left support pole with green color
                mesh = object3D::CreateCube("leftPole", glm::vec3(-0.5f, 0, -0.5f), 1.0f, glm::vec3(0, 1, 0), true); // Solid green
                meshes.push_back(mesh);

                // Create right support pole with green color
                mesh = object3D::CreateCube("rightPole", glm::vec3(-0.5f, 0, -0.5f), 1.0f, glm::vec3(0, 1, 0), true); // Solid green
                meshes.push_back(mesh);
            }
        }

        vector<Mesh*> GetMeshes() const { return meshes; }
        vector<glm::mat4> GetTransforms() const { return transforms; }

        bool IsPassingThrough(const glm::vec3& dronePosition) const {
            float halfWidth = 1.8f; // Half of frameSize
            float tolerance = 0.4f;

            // Check if drone is within the gate boundaries
            bool withinX = dronePosition.x >= position.x - halfWidth &&
                dronePosition.x <= position.x + halfWidth;
            bool withinY = dronePosition.y >= position.y + 2 &&
                dronePosition.y <= position.y + 4;
            bool withinZ = abs(dronePosition.z - position.z) < tolerance;

            return withinX && withinY && withinZ;
        }

    private:
        vector<glm::mat4> transforms;
        vector<Mesh*> meshes;
        bool isPassed = false;
    };
}