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
    class Tree
    {
     public:
        Tree()
        {}

        ~Tree()
        { }

		glm::vec3 position;

		void CreateTree(vector<vector<int>>& pozitiiObiecte, int halfMap, int Random, vector< implemented::Drona::BoundingBox*>& coliziuni_obiecte)
		{
			{
				meshes.clear();

				// the trunk of the tree
				Mesh* mesh = object3D::CreateCilinder("trunk", glm::vec3(0, 0, 0), 1, 1.0f, glm::vec3(0.36f, 0.25f, 0.20f), true);
				meshes.push_back(mesh);

				// coroana copacului
				mesh = object3D::CreateSphere("coroana", glm::vec3(0, 0, 0), 1, glm::vec3(0.196f, 0.804f, 0.196f), true);
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
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 1.5f, 0.2f));
				transforms.push_back(modelMatrix); 
				
				glm::vec3 mmin = glm::vec3(modelMatrix * glm::vec4(min, 1));
				glm::vec3 mmax = glm::vec3(modelMatrix * glm::vec4(max, 1));
				implemented::Drona::BoundingBox* obiect = new implemented::Drona::BoundingBox;
				obiect->minPoint = mmin;
				obiect->maxPoint = mmax;
				coliziuni_obiecte.push_back(obiect);

				//cone1
				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, position + glm::vec3(0, 2, 0));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8f, 0.8f, 0.8f));
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
