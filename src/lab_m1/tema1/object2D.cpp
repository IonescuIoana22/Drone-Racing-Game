#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"
#include <iostream>
using namespace std;


Mesh* object2D::CreateSquare(
    const std::string &name,
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
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateTanc(
    const std::string& name,
    glm::vec3 centre,
	float halfbazamica1,
	float halfbazamare1,
	float inaltime1,
	float halfbazamica2,
	float halfbazamare2,
	float inaltime2,
    float raza,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 centru = centre;
	
	glm::vec3 centru_cerc = centru + glm::vec3(0, inaltime1 + inaltime2, 0);
	int segmente = 100;
	float angle = M_PI / segmente;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(centru + glm::vec3(halfbazamica1, 0, 0), color),
        VertexFormat(centru + glm::vec3(-halfbazamica1, 0, 0), color),
        VertexFormat(centru + glm::vec3(-halfbazamare1, inaltime1, 0), color),
        VertexFormat(centru + glm::vec3(halfbazamare1, inaltime1, 0), color),
        VertexFormat(centru + glm::vec3(-halfbazamare2, inaltime1, 0), color),
		VertexFormat(centru + glm::vec3(halfbazamare2, inaltime1, 0), color),
		VertexFormat(centru + glm::vec3(-halfbazamica2, inaltime1 + inaltime2, 0), color),
		VertexFormat(centru + glm::vec3(halfbazamica2, inaltime1 + inaltime2, 0), color)
    };

    Mesh* tanc = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 2, 3,
        5, 2, 7, 
        2, 4, 6, 
        2, 6, 7
    };

    std::vector<VertexFormat> vertices_cerc = {
		VertexFormat(centru_cerc, color),
    };
	vertices.push_back(VertexFormat(centru_cerc, color));

	float angle1, angle2;
    for (int i = 0; i < segmente + 8; i++) {
		angle1 = i * angle;
		angle2 = (i + 1) * angle;
		vertices.push_back(VertexFormat(centru_cerc + glm::vec3(raza * cos(angle1), raza * sin(angle1), 0), color));
    }
	vertices.push_back(VertexFormat(centru_cerc + glm::vec3(raza * cos(angle2), raza * sin(angle2), 0), color));

    for (int i = 1; i < segmente + 8; i++) {
		indices.push_back(8);
		indices.push_back(i + 8);
		indices.push_back(i + 1 + 8);
    }

    tanc->InitFromData(vertices, indices);

    return tanc;
}

Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 centre,
    float raza,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 centru = centre;
    int segmente = 360;
    float angle = (M_PI * 2) / segmente;

    std::vector<VertexFormat> vertices = {
        VertexFormat(centru, color),
    };
    vertices.push_back(VertexFormat(centru, color));

    float angle1, angle2;
    for (int i = 0; i < segmente + 8; i++) {
        angle1 = i * angle;
        angle2 = (i + 1) * angle;
        vertices.push_back(VertexFormat(centru + glm::vec3(raza * cos(angle1), raza * sin(angle1), 0), color));
    }
    vertices.push_back(VertexFormat(centru + glm::vec3(raza * cos(angle2), raza * sin(angle2), 0), color));

    Mesh* cerc = new Mesh(name);
    std::vector<unsigned int> indices = {};

    for (int i = 1; i < segmente + 8; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    cerc->InitFromData(vertices, indices);
    return cerc;
}

Mesh* object2D::CreateParabola(
    const std::string& name,
	vector<pair<float, float>> puncte,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices = {};

	for (int i = 0; i < puncte.size(); i++) {
		vertices.push_back(VertexFormat(glm::vec3(puncte[i].first, puncte[i].second, 0), color));
	}

    Mesh* parabola = new Mesh(name);
    std::vector<unsigned int> indices = {};

    parabola->SetDrawMode(GL_LINES);

	for (int i = 0; i < puncte.size() - 1; i++) {
		indices.push_back(i);
		indices.push_back(i + 1);
	}

    parabola->InitFromData(vertices, indices);
    return parabola;
}