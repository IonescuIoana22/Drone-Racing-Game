#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema2/camera.h"
#include "lab_m1/tema2/drona.h"
#include "lab_m1/tema2/cladiri.h"
#include "lab_m1/tema2/brazi.h"
#include "lab_m1/tema2/copaci.h"
#include "lab_m1/tema2/harta.h"
#include "lab_m1/tema2/checkpoint.h"
#include "lab_m1/tema2/clouds.h"

#include <vector>

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        Tema2();
        ~Tema2();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, implemented::Camera_tema* camera);
        void Tema2::RenderMeshTimer(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);


        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        implemented::Camera_tema *camera;
		implemented::Camera_tema* cameraMiniMap;
        implemented::Drona* drona;
		implemented::Building* building;
		vector<implemented::Building*> buildings;
		implemented::Brad* brad;
		vector<implemented::Brad*> brazi;
        implemented::Tree* tree;
        vector<implemented::Tree*> trees;
        vector<implemented::Drona::BoundingBox*> coliziune_obiecte;
        glm::mat4 projectionMatrix;
        //bool renderCameraTarget;
		implemented::Map* map;
		implemented::Checkpoint* checkpoint;
		vector<implemented::Checkpoint*> checkpoints;
        vector<implemented::Drona::BoundingBox*> coliziune_checkpoint;
		implemented::Cloud* cloud;
		vector<implemented::Cloud*> clouds;
        vector<vector<int>> pozitiiObiecte;
		int nrCopaci = 0, nrBrazi = 0, nrCheckpoint = 0, nrCladiri = 0, nrClouds = 0;
        int halfMap = 502;
        int droneType = 1;
		int Random = 1000;
        int dist = 200;
        int move = 0;
        int ct_checkpoint = 0;
        float lungime;
    };
}
