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

using namespace std;

namespace implemented
{
    class Cloud
    {
    public:
        Cloud()
        {}
        ~Cloud()
        {}

        glm::vec3 basePosition;

        void CreateCloud1(int Random)
        {
            {
                meshes.clear();
                // Create first sphere of cloud
                Mesh* sphere1 = object3D::CreateSphere("cloud_sphere1",
                    glm::vec3(0, 0, 0), 1.0f,
                    glm::vec3(0.9f, 0.9f, 0.9f), true);
                meshes.push_back(sphere1);

                // Create second sphere of cloud
                Mesh* sphere2 = object3D::CreateSphere("cloud_sphere2",
                    glm::vec3(0, 0, 0), 1.0f,
                    glm::vec3(0.9f, 0.9f, 0.9f), true);
                meshes.push_back(sphere2);
            }
            {
                transforms.clear();
                random_device rd;
                mt19937 generator(rd());
                uniform_real_distribution<float> position_dist(-Random, Random);
                uniform_real_distribution<float> height_dist(10.0, 35.0);

                // Generate random position for the cloud
                float x, z, y;
                do {
                    x = position_dist(generator);
                    z = position_dist(generator);
                    y = height_dist(generator);
                } while (-1 < x && x < 1 && -1 < z && z < 1);

                basePosition = glm::vec3(x, y, z);

                // First sphere transform
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, basePosition);
                modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
                transforms.push_back(modelMatrix);

                // Second sphere transform - slightly offset from the first
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, basePosition + glm::vec3(1.5f, 0.3f, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
                transforms.push_back(modelMatrix);
            }
        }

        void CreateCloud2(int Random)
        {
            {
                meshes.clear();

                // Create smaller spheres for cloud detail
                for (int i = 0; i < 3; i++) {
                    Mesh* smallSphere = object3D::CreateSphere("cloud_small" + std::to_string(i),
                        glm::vec3(0, 0, 0), 0.8f,
                        glm::vec3(0.85f, 0.85f, 0.85f), true);
                    meshes.push_back(smallSphere);
                }
            }

            {
                transforms.clear();
                random_device rd;
                mt19937 generator(rd());
                uniform_real_distribution<float> position_dist(-Random, Random);
                uniform_real_distribution<float> height_dist(10.0, 15.0);

                // Generate random position for the cloud
                float x, z, y;
                do {
                    x = position_dist(generator);
                    z = position_dist(generator);
                    y = height_dist(generator);
                } while (-1 < x && x < 1 && -1 < z && z < 1);

                glm::vec3 basePosition = glm::vec3(x, y, z);

                glm::mat4 modelMatrix = glm::mat4(1);

                // Smaller spheres transforms
                for (int i = 0; i < 3; i++) {
                    modelMatrix = glm::mat4(1);
                    float angle = (float)i * 2.0f * glm::pi<float>() / 3.0f;
                    modelMatrix = glm::translate(modelMatrix,
                        basePosition + glm::vec3(
                            0.8f * cos(angle),
                            0.3f * sin(angle),
                            0.8f * sin(angle)
                        ));
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
                    transforms.push_back(modelMatrix);
                }
            }
        }

        vector<glm::mat4> GetTransforms()
        {
            return transforms;
        }

        vector<Mesh*> GetMeshes()
        {
            return meshes;
        }

    private:
        vector<glm::mat4> transforms;
        vector<Mesh*> meshes;
    };
}