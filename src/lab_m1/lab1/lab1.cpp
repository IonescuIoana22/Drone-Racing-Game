#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <random>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab1::Lab1()
{
    // TODO(student): Never forget to initialize class variables!
    position = glm::vec3(0);
    ct = 0;
    jump = 0;
    culoare = glm::vec3(0);
}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh.
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // TODO(student): Load some more meshes. The value of RESOURCE_PATH::MODELS
    // is actually a path on disk, go there and you will find more meshes.

    {
        Mesh* mesh = new Mesh("sfera");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("teapot");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "teapot.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("arcas");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "characters/archer"), "Archer.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }


}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer

    // TODO(student): Generalize the arguments of `glClearColor`.
    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).
    glClearColor(culoare.x, culoare.y, culoare.z, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render the object
    RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

    // Render the object again but with different properties
    RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

    // TODO(student): We need to render (a.k.a. draw) the mesh that
    // was previously loaded. We do this using `RenderMesh`. Check the
    // signature of this function to see the meaning of its parameters.
    // You can draw the same mesh any number of times.

    RenderMesh(meshes[corp], glm::vec3(3, 0.5f, 0.1f));

    RenderMesh(meshes["arcas"], position, glm::vec3(0.01f));

    if (jump == 1) {
        position.y += 0.05f;
        if (position.y >= 1) {
            jump = -1;
        }
    } else if (jump == -1) {
        position.y -= 0.05f;
        if (position.y <= 0) {
            jump = 0;
        }
    }

}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)     // deltaTime - timp cadru anterior
{
    // Treat continuous update based on input

    // TODO(student): Add some key hold events that will let you move
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.

    if (window->KeyHold(GLFW_KEY_W)) {
        position.z -= 2 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        position.z += 2 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_Q)) {
        position.y -= 2 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        position.y += 2 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_E)) {
        position.x -= 2 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        position.x += 2 * deltaTime;
    }
}


void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_W) {
        // TODO(student): Change the values of the color components.
        cout << "W\n";
    }

    if (key == GLFW_KEY_SPACE) {
        cout << "SPACE\n";
    }

    if (key == GLFW_KEY_P) {
        cout << "P\n";
        random_device rd;  // Sursa de entropie
        mt19937 gen(rd());  // Generator de numere bazat pe Mersenne Twister
        uniform_real_distribution<> dis(0.0, 1.0);  // Distribu?ie uniform? între 0.0 ?i 1.0
        culoare.x = dis(gen);
        culoare.y = dis(gen);
        culoare.z = dis(gen);
    }

    // TODO(student): Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.

    if (key == GLFW_KEY_Y) {
        cout << "Y " << ct << "\n";
        if (ct == 0) {
            corp = "box";
            ct++;
        } else if (ct == 1) {
            corp = "sfera";
            ct++;
        } else if (ct == 2) {
            corp = "teapot";
            ct = 0;
        }
    }

    if (key == GLFW_KEY_O && jump == 0) {
        cout << "O\n";
        position.y += 0.05f;
        jump = 1;
    }
}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
