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
	class Building
	{
	public:
		Building()
		{}

		~Building()
		{ }

		glm::vec3 position;

		void CreateBuilding(vector<vector<int>>& pozitiiObiecte, int halfMap, int Random, vector< implemented::Drona::BoundingBox*>& coliziuni_obiecte)
		{
			{
				meshes.clear();

				// Main building body
				Mesh* mesh = object3D::CreateCube("mainBody", glm::vec3(-0.5, 0, -0.5), 1.0f, glm::vec3(0.698f, 0.698f, 0.698f), true);
				meshes.push_back(mesh);

				// Roof
				mesh = object3D::CreateCube("roof", glm::vec3(-0.5, 0, -0.5), 1.0f, glm::vec3(0.545f, 0.271f, 0.075f), true);
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
				glm::vec3 min = glm::vec3(-0.5, 0, -0.5);
				glm::vec3 max = glm::vec3(0.5, 1, 0.5);

				// Main building transform
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, position);
				modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f, 3.0f, 1.5f));
				transforms.push_back(modelMatrix);

				glm::vec3 mmin = glm::vec3(modelMatrix * glm::vec4(min, 1));
				glm::vec3 mmax = glm::vec3(modelMatrix * glm::vec4(max, 1));
				implemented::Drona::BoundingBox* obiect = new implemented::Drona::BoundingBox;
				obiect->minPoint = mmin;
				obiect->maxPoint = mmax;
				coliziuni_obiecte.push_back(obiect);

				// Roof transform
				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, position + glm::vec3(0, 3.0f, 0));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(2.2f, 0.25f, 1.7f));
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

		vector<Mesh*> GetMesh()
		{
			return meshes;
		}

	private:
		vector<glm::mat4> transforms;
        vector<Mesh*> meshes;
    };
}
