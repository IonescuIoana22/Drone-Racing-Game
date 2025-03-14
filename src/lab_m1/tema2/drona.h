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

using namespace std;


namespace implemented
{
    class Drona
    {
     public:
        Drona()
        {}

        ~Drona()
        { }

		glm::vec3 viteza_totala = glm::vec3(0);
        glm::vec3 position = glm::vec3(0);
		float propellerRotation = glm::radians(0.0f);
		float rotateX = 0, rotateY = 0, rotateZ = 0;
        float viteza = 0;
        float life = 0;
        glm::vec3 pos_checkpoint = glm::vec3(0);

		void CreateDrone1()
		{
			{
				meshes.clear();

				Mesh* mesh = object3D::CreateCube("arm1", glm::vec3(-0.5, 0, -0.5), 1.0f, glm::vec3(0.2f, 0.502f, 0.8f), true);
				meshes.push_back(mesh);

				mesh = object3D::CreateCube("arm2", glm::vec3(-0.5f, 0, -0.5), 1.0f, glm::vec3(0.2f, 0.502f, 0.8f), true);
				meshes.push_back(mesh);

				mesh = object3D::CreateCube("tower1", glm::vec3(-0.5, 0, -0.5), 1.0f, glm::vec3(0.2f, 0.502f, 0.8f), true);
				meshes.push_back(mesh);

				mesh = object3D::CreateCube("tower2", glm::vec3(-0.5, 0, -0.5), 1.0f, glm::vec3(0.2f, 0.502f, 0.8f), true);
				meshes.push_back(mesh);

				mesh = object3D::CreateCube("tower3", glm::vec3(-0.5, 0, -0.5), 1.0f, glm::vec3(0.2f, 0.502f, 0.8f), true);
				meshes.push_back(mesh);

				mesh = object3D::CreateCube("tower4", glm::vec3(-0.5, 0, -0.5), 1.0f, glm::vec3(0.2f, 0.502f, 0.8f), true);
				meshes.push_back(mesh);

				mesh = object3D::CreateCube("wing1", glm::vec3(-0.5, 0, -0.5), 1.0f, glm::vec3(1), true);
				meshes.push_back(mesh);

				mesh = object3D::CreateCube("wing2", glm::vec3(-0.5, 0, -0.5), 1.0f, glm::vec3(1), true);
				meshes.push_back(mesh);

				mesh = object3D::CreateCube("wing3", glm::vec3(-0.5, 0, -0.5), 1.0f, glm::vec3(1), true);
				meshes.push_back(mesh);

				mesh = object3D::CreateCube("wing4", glm::vec3(-0.5, 0, -0.5), 1.0f, glm::vec3(1), true);
				meshes.push_back(mesh);

                mesh = object3D::CreateCube("arrow", glm::vec3(-0.5, 0, 0), 1.0f, glm::vec3(0), true);
                meshes.push_back(mesh);
			}
		}

		void Drone1Transformari()
		{
            {
                transforms.clear();
                glm::mat4 modelMatrix = glm::mat4(1);

                //first arm
                modelMatrix = glm::translate(modelMatrix, position);
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
				modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY), glm::vec3(0, 1, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 0.2f, 0.2f));
                transforms.push_back(modelMatrix);

                //second arm
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position);
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY + 90.0f), glm::vec3(0, 1, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 0.2f, 0.2f));
                transforms.push_back(modelMatrix);

                //tower1
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position);
				modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY), glm::vec3(0, 1, 0));
                modelMatrix = glm::translate(modelMatrix, glm::vec3(0.9f, 0.2f, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
                transforms.push_back(modelMatrix);

                //tower2
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position);
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY), glm::vec3(0, 1, 0));
                modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.9f, 0.2f, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
                transforms.push_back(modelMatrix);

                //tower3
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position);
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY), glm::vec3(0, 1, 0));
                modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.2f, -0.9f));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
                transforms.push_back(modelMatrix);

                //tower4
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position);
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY), glm::vec3(0, 1, 0));
                modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.2f, 0.9f));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
                transforms.push_back(modelMatrix);

                //wing1
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position);
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY), glm::vec3(0, 1, 0));
                modelMatrix = glm::translate(modelMatrix, glm::vec3(0.9f, 0.2f, 0) + glm::vec3(0, 0.2f, 0));
                modelMatrix = glm::rotate(modelMatrix, propellerRotation, glm::vec3(0, 1, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.05f, 0.1f));
                transforms.push_back(modelMatrix);

                //wing2
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position);
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY), glm::vec3(0, 1, 0));
                modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.9f, 0.2f, 0) + glm::vec3(0, 0.2f, 0));
                modelMatrix = glm::rotate(modelMatrix, propellerRotation, glm::vec3(0, 1, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.05f, 0.1f));
                transforms.push_back(modelMatrix);

                //wing3
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position);
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY), glm::vec3(0, 1, 0));
                modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.2f, -0.9f) + glm::vec3(0, 0.2f, 0));
                modelMatrix = glm::rotate(modelMatrix, propellerRotation, glm::vec3(0, 1, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.05f, 0.1f));
                transforms.push_back(modelMatrix);

                //wing4
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position);
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY), glm::vec3(0, 1, 0));
                modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.2f, 0.9f) + glm::vec3(0, 0.2f, 0));
                modelMatrix = glm::rotate(modelMatrix, propellerRotation, glm::vec3(0, 1, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.05f, 0.1f));
                transforms.push_back(modelMatrix);

                // sageata
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position);
                modelMatrix = glm::rotate(modelMatrix, atan2(pos_checkpoint.z - position.z, -pos_checkpoint.x + position.x), glm::vec3(0, 1, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0, 0, 1));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f, 1.5f, 0.05f));
                transforms.push_back(modelMatrix);
            }
		}

        void CreateDrone2()
        {
            {
                meshes.clear();

                // Same mesh creation code as before
                for (int i = 0; i < 6; i++) {
                    Mesh* arm = object3D::CreateCube("arm_" + std::to_string(i), 
                        glm::vec3(-0.5, 0, -0.5), 1.0f, 
                        glm::vec3(0.3f, 0.3f, 0.3f), true);
                    meshes.push_back(arm);
                }

                Mesh* hub = object3D::CreateCube("hub", 
                    glm::vec3(-0.5, 0, -0.5), 1.0f, 
                    glm::vec3(0.2f, 0.2f, 0.2f), true);
                meshes.push_back(hub);

                for (int i = 0; i < 6; i++) {
                    Mesh* motor = object3D::CreateCube("motor_" + std::to_string(i),
                        glm::vec3(-0.5, 0, -0.5), 1.0f,
                        glm::vec3(0.1f, 0.1f, 0.1f), true);
                    meshes.push_back(motor);

                    Mesh* propeller = object3D::CreateCube("propeller_" + std::to_string(i),
                        glm::vec3(-0.5, 0, -0.5), 1.0f,
                        glm::vec3(0.8f), true);
                    meshes.push_back(propeller);
                }

                Mesh* mesh = object3D::CreateCube("arrow", glm::vec3(-0.5, 0, 0), 1.0f, glm::vec3(0), true);
                meshes.push_back(mesh);
            }
        }

        void Drone2Transformari() {
            {
                transforms.clear();
                glm::mat4 modelMatrix;
                float radius = 1.2f;

                // Arms with modified scaling
                for (int i = 0; i < 6; i++) {
                    float angle = i * glm::pi<float>() / 3.0f;
                    modelMatrix = glm::mat4(1);
                    modelMatrix = glm::translate(modelMatrix, position);
                    //modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY) + angle, glm::vec3(0, 1, 0));
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(radius / 2, 0, 0));
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(radius + 0.2f, 0.15f, 0.2f));
                    transforms.push_back(modelMatrix);
                }

                // Hub
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position);
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY), glm::vec3(0, 1, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.2f, 0.5f));
                transforms.push_back(modelMatrix);

                // Motors and propellers maintain their positions
                for (int i = 0; i < 6; i++) {
                    float angle = i * glm::pi<float>() / 3.0f;

                    modelMatrix = glm::mat4(1);
                    modelMatrix = glm::translate(modelMatrix, position);
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY), glm::vec3(0, 1, 0));
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(radius * cos(angle), 0.15f, radius * sin(angle)));
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
                    transforms.push_back(modelMatrix);

                    modelMatrix = glm::mat4(1);
                    modelMatrix = glm::translate(modelMatrix, position);
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY), glm::vec3(0, 1, 0));
					modelMatrix = glm::translate(modelMatrix, glm::vec3(radius * cos(angle), 0.25f, radius * sin(angle)));
                    modelMatrix = glm::rotate(modelMatrix, propellerRotation, glm::vec3(0, 1, 0));
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6f, 0.05f, 0.1f));
                    transforms.push_back(modelMatrix);
                }

                // sageata
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position);
                modelMatrix = glm::rotate(modelMatrix, atan2(pos_checkpoint.z - position.z, -pos_checkpoint.x + position.x), glm::vec3(0, 1, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0, 0, 1));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f, 2.0f, 0.05f));
                transforms.push_back(modelMatrix);
            }
        }

        void CreateDrone3()
        {
            {
                meshes.clear();

                // Same mesh creation code as before
                Mesh* body = object3D::CreateCube("body",
                    glm::vec3(-0.5, 0, -0.5), 1.0f,
                    glm::vec3(0.8f, 0.8f, 0.8f), true);
                meshes.push_back(body);

                for (int i = 0; i < 4; i++) {
                    Mesh* arm = object3D::CreateCube("arm_" + std::to_string(i),
                        glm::vec3(-0.5, 0, -0.5), 1.0f,
                        glm::vec3(0.7f), true);
                    meshes.push_back(arm);
                }

                for (int i = 0; i < 4; i++) {
                    Mesh* motor = object3D::CreateCube("motor_" + std::to_string(i),
                        glm::vec3(-0.5, 0, -0.5), 1.0f,
                        glm::vec3(0.2f), true);
                    meshes.push_back(motor);

                    Mesh* prop = object3D::CreateCube("prop_" + std::to_string(i),
                        glm::vec3(-0.5, 0, -0.5), 1.0f,
                        glm::vec3(0.9f), true);
                    meshes.push_back(prop);
                }
                Mesh* mesh = object3D::CreateCube("arrow", glm::vec3(-0.5, 0, 0), 1.0f, glm::vec3(0), true);
                meshes.push_back(mesh);
            }
        }

		void Drone3Transformari() {
            {
                transforms.clear();
                glm::mat4 modelMatrix;
                float radius = 1.0f;

                // Body
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position);
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY), glm::vec3(0, 1, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8f, 0.25f, 0.6f));
                transforms.push_back(modelMatrix);

                // Arms
                for (int i = 0; i < 4; i++) {
                    float angle = i * glm::pi<float>() / 2.0f;
                    modelMatrix = glm::mat4(1);
                    modelMatrix = glm::translate(modelMatrix, position);
                    //modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY) + angle, glm::vec3(0, 1, 0));
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(radius / 2, 0, 0));
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(radius + 0.20f, 0.1f, 0.2f));
                    transforms.push_back(modelMatrix);
                }

                // Motors and props maintain their positions
                for (int i = 0; i < 4; i++) {
                    float angle = i * glm::pi<float>() / 2.0f;

                    modelMatrix = glm::mat4(1);
                    modelMatrix = glm::translate(modelMatrix, position);
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY), glm::vec3(0, 1, 0));
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(radius * cos(angle), 0.10f, radius * sin(angle)));
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
                    transforms.push_back(modelMatrix);

                    modelMatrix = glm::mat4(1);
                    modelMatrix = glm::translate(modelMatrix, position);
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateX), glm::vec3(1, 0, 0));
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateZ), glm::vec3(0, 0, 1));
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateY), glm::vec3(0, 1, 0));
					modelMatrix = glm::translate(modelMatrix, glm::vec3(radius * cos(angle), 0.20f, radius * sin(angle)));
                    modelMatrix = glm::rotate(modelMatrix, propellerRotation, glm::vec3(0, 1, 0));
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.05f, 0.1f));
                    transforms.push_back(modelMatrix);
                }

                // sageata
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, position);
                modelMatrix = glm::rotate(modelMatrix, atan2(pos_checkpoint.z - position.z, -pos_checkpoint.x + position.x), glm::vec3(0, 1, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0, 0, 1));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f, 1.5f, 0.05f));
                transforms.push_back(modelMatrix);
            }
		}

        void ChangeSpeed(float speed) {
			viteza += speed * 0.5f;
            if (viteza > 1)
				viteza = 1;
        }

        void Update(float deltaTime, int droneType, int move) {
            if (move == 1 && life <= 0) {
                glm::vec3 normalY = glm::vec3(0, 1, 0);
                glm::mat4 MatrixX = glm::rotate(glm::mat4(1.0f), glm::radians(rotateX), glm::vec3(1, 0, 0));
                glm::mat4 MatrixY = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 1, 0));
                glm::mat4 MatrixZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotateZ), glm::vec3(0, 0, 1));
                glm::mat4 rotationMatrix = MatrixX * MatrixZ * MatrixY;
                glm::vec4 rotate_vecY = rotationMatrix * glm::vec4(normalY, 1.0f);
                if (viteza > 0) {
                    normalY = glm::normalize(glm::vec3(rotate_vecY));
                }
                viteza_totala = normalY * viteza;

                position += viteza_totala;
			    viteza -= deltaTime * 0.1f;

                if (viteza < -0.5f) {
                    viteza = -0.5f;
                }
            }

            if (life > 0 && move == 1) {
                position -= viteza_totala;
                life -= 20 * deltaTime;
            }

            if (position.y < 0) {
                position.y = 0;
				viteza = 0;
            }

            if (position.x > 503) {
				position.x = -503;
            } else if (position.x < -503) {
				position.x = 503;
            } else if (position.z > 503) {
                position.z = -503;
            } else if (position.z < -503) {
                position.z = 503;
            }

            if (droneType == 1) {
                Drone1Transformari();
            }
            else if (droneType == 2) {
                Drone2Transformari();
            }
            else if (droneType == 3) {
                Drone3Transformari();
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

        struct BoundingBox {
            glm::vec3 minPoint;
            glm::vec3 maxPoint;
        };

        // Get the drone's current bounding box
        BoundingBox getBoundingBox() const {
            BoundingBox box;
            float radius = 1.0f; // Using the largest radius among drone types
            float height = 0.5f; // Approximate height including propellers

            // Calculate box dimensions based on drone position and size
            box.minPoint = position + viteza + glm::vec3(-radius, -0.2f, -radius);
            box.maxPoint = position + viteza + glm::vec3(radius, height, radius);

            return box;
        }

        // Check collision with another box
        bool checkCollision(const BoundingBox& other) const {
            BoundingBox drone = getBoundingBox();

            return (drone.minPoint.x <= other.maxPoint.x &&
                drone.maxPoint.x >= other.minPoint.x &&
                drone.minPoint.y <= other.maxPoint.y &&
                drone.maxPoint.y >= other.minPoint.y &&
                drone.minPoint.z <= other.maxPoint.z &&
                drone.maxPoint.z >= other.minPoint.z);
        }

	private:
		vector<glm::mat4> transforms;
        vector<Mesh*> meshes;
    };
}
