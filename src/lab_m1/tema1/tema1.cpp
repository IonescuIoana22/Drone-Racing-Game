#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>
#include <cmath>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"
#include "tema1.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


tema1::tema1()
{
}


tema1::~tema1()
{
}

float tema1::creare_functie(int x)
{//+ 70 * sin((PI / 200) * x)
    //return 200 * sin((PI / 500) * x) + 10 * sin((PI / 200) * x) + 100 * sin((PI / 300) * x) + 10 * sin((PI / 200) * x)  + 250;
    //return 200 * sin((PI / 900) * x) + 50 * sin((PI / 700) * x) + 30 * sin((PI / 250) * x) + 10 * sin((PI / 300) * x) + 250;
    return (float)200 * sin((M_PI / 900) * x) + 50 * sin((M_PI / 700) * x) + 30 * sin((M_PI / 250) * x) + 19 * sin((M_PI / 100) * x) + 250;
}


void tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

	// am calculat inaltimea terenului in fiecare punct si am creat matricile de modelare pentru fiecare patrat
	for (int i = 0; i <= resolution.x + 1; i++) {
		mapa.push_back(creare_functie(i));
		if (i != 0) {
            modelMatrix = glm::mat3(1);
            modelMatrix = transform2D::Scale(i - 1, mapa[i - 1], i, mapa[i]) * modelMatrix;
            modelMatrix = transform2D::Forfecare(i - 1, mapa[i - 1], i, mapa[i]) * modelMatrix;
            modelMatrix = transform2D::Translate(i - 1, mapa[i - 1]) * modelMatrix;
			matrici_modelare.push_back(modelMatrix);
		}
	}
    
    glm::vec3 corner = glm::vec3(0, -1, 0);
    float squareSide = 1;
	pozitietanc1 = glm::vec3(10, mapa[10], 0);
	pozitietanc2 = glm::vec3(1250, mapa[1250], 0);
	pozitieteava1 = glm::vec3(12, 26, 0);
	pozitieteava2 = glm::vec3(12, 26, 0);

    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 1, 0.5f), true);
    AddMeshToList(square1);

	Mesh* tanc1 = object2D::CreateTanc("tanc1", glm::vec3(0, -1.5f, 0), 20, 30, 10, 28, 40, 16, 12, glm::vec3(0.255f, 0.412f, 0.882f), true);
	AddMeshToList(tanc1);

    Mesh* tanc2 = object2D::CreateTanc("tanc2", glm::vec3(0, -1.5f, 0), 20, 30, 10, 28, 40, 16, 12, glm::vec3(0.933f, 0.510f, 0.933f), true);
    AddMeshToList(tanc2);

	Mesh* teava = object2D::CreateSquare("teava", glm::vec3(0, 0, 0), 10, glm::vec3(0, 0, 0), true);
	AddMeshToList(teava);

    Mesh* bila = object2D::CreateCircle("bila", glm::vec3(0), 6, glm::vec3(0, 0, 0), true);
    AddMeshToList(bila);

	Mesh* contur_hp1 = object2D::CreateSquare("contur_hp1", glm::vec3(0, 0, 0), 50, glm::vec3(0, 0, 0), false);
	AddMeshToList(contur_hp1);

	Mesh* contur_hp2 = object2D::CreateSquare("contur_hp2", glm::vec3(0, 0, 0), 50, glm::vec3(0, 0, 0), false);
	AddMeshToList(contur_hp2);

	Mesh* bara_hp1 = object2D::CreateSquare("bara_hp1", glm::vec3(0, 0, 0), 50, glm::vec3(1, 1, 1), true);
	AddMeshToList(bara_hp1);

	Mesh* bara_hp2 = object2D::CreateSquare("bara_hp2", glm::vec3(0, 0, 0), 50, glm::vec3(1, 1, 1), true);
	AddMeshToList(bara_hp2);

	Mesh* soare = object2D::CreateCircle("soare", glm::vec3(100, 100, 0), 50, glm::vec3(1, 1, 0), true);
	AddMeshToList(soare);

    Mesh* nor = object2D::CreateCircle("nor", glm::vec3(100, 100, 0), 30, glm::vec3(1, 1, 1), true);
    AddMeshToList(nor);
}


void tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.529f, 0.808f, 0.922f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void tema1::Update(float deltaTimeSeconds)
{
	// am creat terenul
    for (int i = 1; i < matrici_modelare.size(); i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix = transform2D::Scale(i - 1, mapa[i - 1], i, mapa[i]) * modelMatrix;
        modelMatrix = transform2D::Forfecare(i - 1, mapa[i - 1], i, mapa[i]) * modelMatrix;
        modelMatrix = transform2D::Translate(i - 1, mapa[i - 1]) * modelMatrix;
        matrici_modelare[i - 1] = modelMatrix;
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], matrici_modelare[i - 1]);
    }

	// am creat norii
    for (int i = 0; i < 3; i++) {
        matrice = glm::mat3(1);
        matrice = transform2D::Translate(i * 45 - 150, 500) * matrice;
        RenderMesh2D(meshes["nor"], shaders["VertexColor"], matrice);
    }

    for (int i = 0; i < 3; i++) {
		matrice = glm::mat3(1);
		matrice = transform2D::Translate(100 + i * 45, 500) * matrice;
		RenderMesh2D(meshes["nor"], shaders["VertexColor"], matrice);
    }
    for (int i = 0; i < 3; i++) {
        matrice = glm::mat3(1);
        matrice = transform2D::Translate(100 + i * 45, 530) * matrice;
        RenderMesh2D(meshes["nor"], shaders["VertexColor"], matrice);
    }

    for (int i = 0; i < 3; i++) {
		matrice = glm::mat3(1);
		matrice = transform2D::Translate(700 + i * 45, 500) * matrice;
		RenderMesh2D(meshes["nor"], shaders["VertexColor"], matrice);
    }
    for (int i = 0; i < 3; i++) {
        matrice = glm::mat3(1);
        matrice = transform2D::Translate(700 + i * 45, 530) * matrice;
        RenderMesh2D(meshes["nor"], shaders["VertexColor"], matrice);
    }

    for (int i = 0; i < 3; i++) {
        matrice = glm::mat3(1);
        matrice = transform2D::Translate(1000 + i * 45, 500) * matrice;
        RenderMesh2D(meshes["nor"], shaders["VertexColor"], matrice);
    }

    for (int i = 0; i < 3; i++) {
        matrice = glm::mat3(1);
        matrice = transform2D::Translate(400 + i * 45, 500) * matrice;
        RenderMesh2D(meshes["nor"], shaders["VertexColor"], matrice);
    }
    
	// am creat soarele
    RenderMesh2D(meshes["soare"], shaders["VertexColor"], transform2D::Translate(1000, 500));

    // alunecarea de teren
    for (int i = 1; i < mapa.size(); i++) {
        if (mapa[i] - mapa[i - 1] > prag) {
            for (int i = 2; i < mapa.size(); i++) {
                float medie = (mapa[i - 2] + mapa[i - 1] + mapa[i]) / 3.0f;
                mapa[i - 2] += (medie - mapa[i - 2]) * deltaTimeSeconds * 2;
                mapa[i - 1] += (medie - mapa[i - 1]) * deltaTimeSeconds * 2;
                mapa[i] += (medie - mapa[i]) * deltaTimeSeconds * 2;
            }
        }
    }
    
	// am creat tancurile, tevile si hp-urile
	if (!(pozitietanc1.x > mapa.size() - 1) && (pozitietanc1.x >= 0) && hp_1 > 0) {
		a1 = floor(pozitietanc1.x);
        b1 = floor(pozitietanc1.x) + 1;
        t1 = (mapa[b1] - mapa[a1])/(b1 - a1);
        pozitietanc1.y = mapa[a1] + t1 * (mapa[b1] - mapa[a1]);

        modelMatrix = glm::mat3(1);
	    modelMatrix *= transform2D::Translate(pozitietanc1.x, pozitietanc1.y);
        modelMatrix *= transform2D::Rotate(atan2(mapa[b1] - mapa[a1], 1));
	    RenderMesh2D(meshes["tanc1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(pozitietanc1.x, pozitietanc1.y - 1.5f);
        modelMatrix *= transform2D::Rotate(atan2(mapa[b1] - mapa[a1], 1));
		modelMatrix *= transform2D::Translate(-1.5f, pozitieteava1.y);
		modelMatrix *= transform2D::Rotate(unghiTun1);
        modelMatrix *= transform2D::ScaleTeava(-4, 0.5f);
		RenderMesh2D(meshes["teava"], shaders["VertexColor"], modelMatrix);

        ptv1_x = modelMatrix[2][0];
        ptv1_y = modelMatrix[2][1];

		modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(pozitietanc1.x, pozitietanc1.y);
        modelMatrix *= transform2D::Rotate(atan2(mapa[b1] - mapa[a1], 1));
		modelMatrix *= transform2D::Translate(-25, 50);
		modelMatrix *= transform2D::ScaleTeava(1.0f * hp_1/100, 0.2f);
		RenderMesh2D(meshes["bara_hp1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(pozitietanc1.x, pozitietanc1.y);
        modelMatrix *= transform2D::Rotate(atan2(mapa[b1] - mapa[a1], 1));
        modelMatrix *= transform2D::Translate(-25, 50);
        modelMatrix *= transform2D::ScaleTeava(1.0f, 0.2f);
        RenderMesh2D(meshes["contur_hp1"], shaders["VertexColor"], modelMatrix);
	}
   
    if (!(pozitietanc2.x > mapa.size() - 1) && (pozitietanc2.x >= 0) && hp_2 > 0) {
        a2 = floor(pozitietanc2.x);
        b2 = floor(pozitietanc2.x) + 1;
        t2 = (mapa[b2] - mapa[a2]) / (b2 - a2);
        pozitietanc2.y = mapa[a2] + t2 * (mapa[b2] - mapa[a2]);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(pozitietanc2.x, pozitietanc2.y);
        modelMatrix *= transform2D::Rotate(atan2(mapa[b2] - mapa[a2], 1));
        RenderMesh2D(meshes["tanc2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(pozitietanc2.x, pozitietanc2.y - 1.5f);
        modelMatrix *= transform2D::Rotate(atan2(mapa[b2] - mapa[a2], 1));
        modelMatrix *= transform2D::Translate(1.5f, pozitieteava2.y);
		modelMatrix *= transform2D::Rotate(unghiTun2);
        modelMatrix *= transform2D::ScaleTeava(4, 0.5f);
        RenderMesh2D(meshes["teava"], shaders["VertexColor"], modelMatrix);

        ptv2_x = modelMatrix[2][0];
        ptv2_y = modelMatrix[2][1];

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(pozitietanc2.x, pozitietanc2.y);
        modelMatrix *= transform2D::Rotate(atan2(mapa[b2] - mapa[a2], 1));
        modelMatrix *= transform2D::Translate(-25, 50);
        modelMatrix *= transform2D::ScaleTeava(1.0f * hp_2/100, 0.2f);
        RenderMesh2D(meshes["bara_hp2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(pozitietanc2.x, pozitietanc2.y);
        modelMatrix *= transform2D::Rotate(atan2(mapa[b2] - mapa[a2], 1));
        modelMatrix *= transform2D::Translate(-25, 50);
        modelMatrix *= transform2D::ScaleTeava(1.0f, 0.2f);
        RenderMesh2D(meshes["contur_hp2"], shaders["VertexColor"], modelMatrix);
        
    }

    // am desenat parabolele
	parabola1.clear();
	parabola2.clear();

    for (int i = 0; i < 500; i++) {
        pair<float, float> p1, p2;
        p1.first = ptv1_x + (-cos(unghiTun1 + (atan2(mapa[b1] - mapa[a1], 1)))) * magnitudine * i * 2 * deltaTimeSeconds;
        p1.second = ptv1_y + (-sin(unghiTun1 + (atan2(mapa[b1] - mapa[a1], 1)))) * magnitudine * i * 2 * deltaTimeSeconds - g * i * i * deltaTimeSeconds * deltaTimeSeconds * 2;
		parabola1.push_back(p1);

        p2.first = ptv2_x + (cos(unghiTun2 + (atan2(mapa[b2] - mapa[a2], 1)))) * magnitudine * deltaTimeSeconds * i * 2;
        p2.second = ptv2_y + (sin(unghiTun2 + (atan2(mapa[b2] - mapa[a2], 1)))) * magnitudine * deltaTimeSeconds * i * 2 - g * i * i * 2 * deltaTimeSeconds * deltaTimeSeconds;
        parabola2.push_back(p2);
    }

	Mesh* parabola_1 = object2D::CreateParabola("parabola1", parabola1, glm::vec3(0, 0, 0), true);
	RenderMesh2D(parabola_1, shaders["VertexColor"], glm::mat3(1));

	Mesh* parabola_2 = object2D::CreateParabola("parabola2", parabola2, glm::vec3(0, 0, 0), true);
	RenderMesh2D(parabola_2, shaders["VertexColor"], glm::mat3(1));

	// am creat proiectilele si am verificat coliziunile
    for (int i = 0; i < pozitieproiectil1.size(); i++) {
		// modific pozitia si viteza proiectilului 
        pozitieproiectil1[i] += vitezaproiectil1[i] * (deltaTimeSeconds * 2);

        vitezaproiectil1[i].y -= g * deltaTimeSeconds * 2;
            
		// afisez proiectilul in aer
        if (pozitieproiectil1[i].y >= 0 && coliziune1[i] == false) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(pozitieproiectil1[i].x, pozitieproiectil1[i].y);
            RenderMesh2D(meshes["bila"], shaders["VertexColor"], modelMatrix);
        }

		// verific daca proiectilul a lovit tancul
        float x = (pozitieproiectil1[i].x - ptv2_x);
        float y = (pozitieproiectil1[i].y - ptv2_y);
        if (sqrt(x * x + y * y) <= raza_tanc && coliziune1[i] == false) {
            coliziune1[i] = true;
            // scad hp
			hp_2 -= 10;
			if (hp_2 <= 0) {
                ptv2_x = -100;
				ptv2_y = -100;
			}
        }

		// verific daca proiectilul a lovit terenul si deformez terenul
        float aux;
        for (int j = 0; j < mapa.size(); j++) {
            if (abs(pozitieproiectil1[i].x - j) < coliziune && pozitieproiectil1[i].y <= mapa[j] && coliziune1[i] == false) {
				
                int k = j - raza, final = j + raza;

                if (j - raza < 0) {
                    k = 0;
                }
                if (j + raza > mapa.size() - 1) {
                    final = mapa.size() - 1;
                }

                while (k <= final) {
                    aux = pozitieproiectil1[i].y - sqrt(raza * raza - (pozitieproiectil1[i].x - k) * (pozitieproiectil1[i].x - k));
				    if (aux < pozitieproiectil1[i].y) {
                        if (aux > 0) {
							if (mapa[k] > aux) {
								mapa[k] = aux;
							}
                        }
					    else {
						    mapa[k] = 0;
					    }
				    }
                    k++;
                }
              
				coliziune1[i] = true;
            } 
        }
    }
    
	// am creat proiectilele si am verificat coliziunile
    for (int i = 0; i < pozitieproiectil2.size(); i++) {
        pozitieproiectil2[i] += vitezaproiectil2[i] * (deltaTimeSeconds * 2);

        vitezaproiectil2[i].y -= g * deltaTimeSeconds * 2;

        if (pozitieproiectil2[i].y >= 0 && coliziune2[i] == false) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(pozitieproiectil2[i].x, pozitieproiectil2[i].y);
            RenderMesh2D(meshes["bila"], shaders["VertexColor"], modelMatrix);
        }

        float x = (pozitieproiectil2[i].x - ptv1_x);
        float y = (pozitieproiectil2[i].y - ptv1_y);
        if (sqrt(x * x + y * y) <= raza_tanc && coliziune2[i] == false) {
			coliziune2[i] = true;
            // scad hp
			hp_1 -= 10;
			if (hp_1 <= 0) {
				ptv1_x = -100;
				ptv1_y = -100;
			}
        }

        float aux;
        for (int j = 0; j < mapa.size(); j++) {
            if (abs(pozitieproiectil2[i].x - j) < coliziune && pozitieproiectil2[i].y <= mapa[j] && coliziune2[i] == false) {

                int k = j - raza, final = j + raza;

                if (j - raza < 0) {
                    k = 0;
                }
                if (j + raza > mapa.size() - 1) {
                    final = mapa.size() - 1;
                }

                while (k <= final) {
                    aux = pozitieproiectil2[i].y - sqrt(raza * raza - (pozitieproiectil2[i].x - k) * (pozitieproiectil2[i].x - k));
                    if (aux < pozitieproiectil2[i].y) {
                        if (aux > 0) {
                            if (mapa[k] > aux) {
                                mapa[k] = aux;
                            }
                        }
                        else {
                            mapa[k] = 0;
                        }
                    }
                    k++;
                }

                coliziune2[i] = true;
            }
        }
    }
}


void tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W))
	{
		// Move the square up
		unghiTun1 += deltaTime;
	}
    if (window->KeyHold(GLFW_KEY_S)) {
		unghiTun1 -= deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_D))
	{
		// Move the square up
		pozitietanc1.x += deltaTime * 100;
	}
    if (window->KeyHold(GLFW_KEY_A))
    {
        // Move the square down
        pozitietanc1.x -= deltaTime * 100;
    }

	if (window->KeyHold(GLFW_KEY_UP))
	{
		// Move the square up
		unghiTun2 -= deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_DOWN)) {
		unghiTun2 += deltaTime;
	}
    if (window->KeyHold(GLFW_KEY_RIGHT))
    {
        // Move the square up
        pozitietanc2.x += deltaTime * 100;
    }
    if (window->KeyHold(GLFW_KEY_LEFT))
    {
        // Move the square down
        pozitietanc2.x -= deltaTime * 100;
    }
}


void tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event

	// am creat pozitia initiala a proiectilului si viteza lui
    if (key == GLFW_KEY_SPACE) {
        proiectil_lansat = true;

        pozitieproiectil1.push_back(glm::vec3(ptv1_x, ptv1_y, 0));

        vitezaproiectil1.push_back(glm::vec3(-cos(unghiTun1 + (atan2(mapa[b1] - mapa[a1], 1))), -sin(unghiTun1 + (atan2(mapa[b1] - mapa[a1], 1))), 0) * magnitudine);

		coliziune1.push_back(false);
    }
    if (key == GLFW_KEY_ENTER) {
        proiectil_lansat = true;

		pozitieproiectil2.push_back(glm::vec3(ptv2_x, ptv2_y, 0));

        vitezaproiectil2.push_back(glm::vec3(cos(unghiTun2 + (atan2(mapa[b2] - mapa[a2], 1))), sin(unghiTun2 + (atan2(mapa[b2] - mapa[a2], 1))), 0) * magnitudine);

		coliziune2.push_back(false);
    }
}


void tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void tema1::OnWindowResize(int width, int height)
{
}