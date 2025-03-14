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
    class Brad
    {
     public:
        Brad()
        {}

        ~Brad()
        { }

		glm::vec3 position;

		void CreateBrad(vector<vector<int>>& pozitiiObiecte, int halfMap, int Random, vector< implemented::Drona::BoundingBox*>& coliziuni_obiecte)
		{
			{
				meshes.clear();

				// the trunk of the Brad
				Mesh* mesh = object3D::CreateCilinder("trunk", glm::vec3(0, 0, 0), 1, 1.0f, glm::vec3(0.545f, 0.271f, 0.075f), true);
				meshes.push_back(mesh);

				// the first cone for the Brad
				mesh = object3D::CreateCone("cone1", glm::vec3(0, 0, 0), 1, 1.0f, glm::vec3(0.133f, 0.545f, 0.133f), true);
				meshes.push_back(mesh);

				// the second cone for the Brad
				mesh = object3D::CreateCone("cone2", glm::vec3(0, 0, 0), 1, 1.0f, glm::vec3(0.133f, 0.635f, 0.133f), true);
				meshes.push_back(mesh);
			}

			{
				transforms.clear();

				random_device rd;
				mt19937 generator(rd());

				uniform_int_distribution<int> distribution(-Random, Random);

				int x, z;
				do {
					x = distribution(generator);
					z = distribution(generator);
				} while (pozitiiObiecte[x + halfMap][z + halfMap] == 1 || pozitiiObiecte[x + halfMap][z + halfMap + 1] == 1 || pozitiiObiecte[x + halfMap][z + halfMap - 1] == 1 ||
					pozitiiObiecte[x + halfMap - 1][z + halfMap] == 1 || pozitiiObiecte[x + halfMap - 1][z + halfMap + 1] == 1 || pozitiiObiecte[x + halfMap - 1][z + halfMap - 1] == 1 ||
					pozitiiObiecte[x + halfMap + 1][z + halfMap] == 1 || pozitiiObiecte[x + halfMap + 1][z + halfMap + 1] == 1 || pozitiiObiecte[x + halfMap + 1][z + halfMap - 1] == 1);

				pozitiiObiecte[x + halfMap][z + halfMap] = 1;
				pozitiiObiecte[x + halfMap][z + halfMap + 1] = 1;
				pozitiiObiecte[x + halfMap][z + halfMap - 1] = 1;
				pozitiiObiecte[x + halfMap - 1][z + halfMap] = 1;
				pozitiiObiecte[x + halfMap - 1][z + halfMap + 1] = 1;
				pozitiiObiecte[x + halfMap - 1][z + halfMap - 1] = 1;
				pozitiiObiecte[x + halfMap + 1][z + halfMap] = 1;
				pozitiiObiecte[x + halfMap + 1][z + halfMap + 1] = 1;
				pozitiiObiecte[x + halfMap + 1][z + halfMap - 1] = 1;

				position = glm::vec3(x, 0, z);
				glm::vec3 min = glm::vec3(-1, 0, -1);
				glm::vec3 max = glm::vec3(1, 1, 1);

				//trunk
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, position);
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 1, 0.2f));
				transforms.push_back(modelMatrix);

				glm::vec3 mmin = glm::vec3(modelMatrix * glm::vec4(min, 1));
				glm::vec3 mmax = glm::vec3(modelMatrix * glm::vec4(max, 1));
				implemented::Drona::BoundingBox* obiect = new implemented::Drona::BoundingBox;
				obiect->minPoint = mmin;
				obiect->maxPoint = mmax;
				coliziuni_obiecte.push_back(obiect);

				//cone1
				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, position + glm::vec3(0, 0.8f, 0));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1.7f, 1));
				transforms.push_back(modelMatrix);

				mmin = glm::vec3(modelMatrix * glm::vec4(min, 1));
				mmax = glm::vec3(modelMatrix * glm::vec4(max, 1));
				obiect = new implemented::Drona::BoundingBox;
				obiect->minPoint = mmin;
				obiect->maxPoint = mmax;
				coliziuni_obiecte.push_back(obiect);

				//cone2
				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, position + glm::vec3(0, 1.9f, 0));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6f, 1, 0.6f));
				transforms.push_back(modelMatrix);

				mmin = glm::vec3(modelMatrix * glm::vec4(min, 1));
				mmax = glm::vec3(modelMatrix * glm::vec4(max, 1));
				obiect = new implemented::Drona::BoundingBox;
				obiect->minPoint = mmin;
				obiect->maxPoint = mmax;
				coliziuni_obiecte.push_back(obiect);
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
