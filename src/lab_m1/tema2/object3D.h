#pragma once

#include <string>
#include <vector>
#include <utility>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

using namespace std;


namespace object3D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateCube(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateCilinder(const std::string& name, glm::vec3 center, float radius, float height, glm::vec3 color, bool fill = false);
	Mesh* CreateCone(const std::string& name, glm::vec3 center, float radius, float height, glm::vec3 color, bool fill = false);
	Mesh* CreateSphere(const std::string& name, glm::vec3 center, float radius, glm::vec3 color, bool fill = false);
	Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
}
