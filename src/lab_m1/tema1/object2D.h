#pragma once

#include <string>
#include <vector>
#include <utility>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

using namespace std;


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateTanc(const std::string &name, glm::vec3 centre, float halfbazamica1, float halfbazamare1, float inaltime1, float halfbazamica2, float halfbazamare2, float inaltime2, float raza, glm::vec3 color, bool fill = false);
    Mesh* CreateCircle(const std::string& name, glm::vec3 centru, float raza, glm::vec3 color, bool fill = false);
	Mesh* CreateParabola(const std::string& name, vector<pair<float, float>> puncte, glm::vec3 color, bool fill = false);
}
