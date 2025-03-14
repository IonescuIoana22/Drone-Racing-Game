#pragma once

#include "components/simple_scene.h"
#include <vector>
#include <utility>

using namespace std;


namespace m1
{
    class tema1 : public gfxc::SimpleScene
    {
     public:
        tema1();
        ~tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        float creare_functie(int x);

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        // TODO(student): If you need any other class variables, define them here.
        glm::mat3 matrice;
        vector<float> mapa;
        vector<glm::mat3> matrici_modelare;
        glm::vec3 pozitietanc1, pozitietanc2, pozitieteava1, pozitieteava2;
        vector<glm::vec3> pozitieproiectil1, vitezaproiectil1, pozitieproiectil2, vitezaproiectil2;
		vector<bool> coliziune1, coliziune2;
        float magnitudine = 150, g = 40, unghiTun1 = M_PI, unghiTun2 = M_PI;
		bool proiectil_lansat = false;
        float a1, a2, b1, b2, t1, t2;
		float ptv1_x, ptv1_y, ptv2_x, ptv2_y;
        float coliziune = 0.75f, raza = 25, raza_tanc = 39;
		float hp_1 = 100, hp_2 = 100;
        float prag = 5;
		vector<pair<float, float>> parabola1, parabola2;
    };
}   // namespace m1
