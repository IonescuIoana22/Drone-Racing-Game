#include "lab_m1/tema2/tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <random>

using namespace std;
using namespace m1;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	camera = new implemented::Camera_tema();
	cameraMiniMap = new implemented::Camera_tema();

	drona = new implemented::Drona();
	map = new implemented::Map(Random + 5, Random + 5);

	lungime = 2.03f;

	Mesh* timer = object3D::CreateSquare("timer", glm::vec3(0.5f, 0, 0), 1, glm::vec3(1, 0, 0), true);
	AddMeshToList(timer);

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	// initialize the pozitiiObiecte vector
	for (int i = 0; i < Random + 5; i++) {
		vector<int> v;
		for (int j = 0; j < Random + 5; j++) {
			v.push_back(0);
		}
		pozitiiObiecte.push_back(v);
	}

	// the position for drone
	pozitiiObiecte[0 + halfMap][0 + halfMap] = 1;
	pozitiiObiecte[0 + halfMap][1 + halfMap] = 1;
	pozitiiObiecte[0 + halfMap][-1 + halfMap] = 1;
	pozitiiObiecte[1 + halfMap][0 + halfMap] = 1;
	pozitiiObiecte[1 + halfMap][1 + halfMap] = 1;
	pozitiiObiecte[1 + halfMap][-1 + halfMap] = 1;
	pozitiiObiecte[-1 + halfMap][0 + halfMap] = 1;
	pozitiiObiecte[-1 + halfMap][1 + halfMap] = 1;
	pozitiiObiecte[-1 + halfMap][-1 + halfMap] = 1;

	nrBrazi = 250;
	nrCopaci = 230;
	nrCheckpoint = 10;
	nrCladiri = 200;
	nrClouds = 5000;

	buildings.clear();
	for (int i = 0; i < nrCladiri; i++) {
		building = new implemented::Building();
		building->CreateBuilding(pozitiiObiecte, halfMap, Random / 2, coliziune_obiecte);
		buildings.push_back(building);

	}

	brazi.clear();
	for (int i = 0; i < nrBrazi; i++) {
		brad = new implemented::Brad();
		brad->CreateBrad(pozitiiObiecte, halfMap, Random / 2, coliziune_obiecte);
		brazi.push_back(brad);
	}

	trees.clear();
	for (int i = 0; i < nrCopaci; i++) {
		tree = new implemented::Tree();
		tree->CreateTree(pozitiiObiecte, halfMap, Random / 2, coliziune_obiecte);
		trees.push_back(tree);
	}

	glm::vec3 color = glm::vec3(1);
	checkpoints.clear();
	for (int i = 0; i < nrCheckpoint; i++) {
		checkpoint = new implemented::Checkpoint();
		checkpoint->CreateCheckpoint(pozitiiObiecte, halfMap, Random / 2, coliziune_checkpoint);
		checkpoints.push_back(checkpoint);
	}
	checkpoints[0]->ChangeMesh(glm::vec3(1, 0, 0));
	drona->pos_checkpoint = checkpoints[0]->position;

	clouds.clear();
	for (int i = 0; i < nrClouds; i++) {
		cloud = new implemented::Cloud();
		cloud->CreateCloud1(Random);
		clouds.push_back(cloud);
		cloud = new implemented::Cloud();
		cloud->CreateCloud2(Random);
		clouds.push_back(cloud);
	}

	// Create a shader program for drawing 3D objects
	{
		Shader* shader = new Shader("LabShader");
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}


void Tema2::FrameStart()
{
	glClearColor(0.15f, 0, 0.85f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
	// the map
	{
		RenderSimpleMesh(map->GetMesh(), shaders["LabShader"], glm::mat4(1), camera);
	}

	// Render the clouds
	{
		for (int i = 0; i < clouds.size(); i++) {
			for (int j = 0; j < clouds[i]->GetMeshes().size(); j++) {
				float x = clouds[i]->basePosition.x - drona->position.x;
				float z = clouds[i]->basePosition.z - drona->position.z;
				if (sqrt(x * x + z * z) < dist) {
					RenderMesh(clouds[i]->GetMeshes()[j], shaders["VertexColor"], clouds[i]->GetTransforms()[j]);
				}
			}
		}
	}

	// Render the checkpoints
	{
		for (int i = ct_checkpoint; i < checkpoints.size(); i++) {
			float x = checkpoints[i]->position.x - drona->position.x;
			float z = checkpoints[i]->position.z - drona->position.z;
			if (sqrt(x * x + z * z) < dist) {
				RenderMesh(checkpoints[i]->GetMeshes()[0], shaders["VertexColor"], checkpoints[i]->GetTransforms()[0]);
				RenderMesh(checkpoints[i]->GetMeshes()[1], shaders["VertexColor"], checkpoints[i]->GetTransforms()[1]);
				RenderMesh(checkpoints[i]->GetMeshes()[2], shaders["VertexColor"], checkpoints[i]->GetTransforms()[2]);
			}
			if (checkpoints[i]->IsPassingThrough(drona->position) && ct_checkpoint == i) {
				checkpoints[i + 1]->ChangeMesh(glm::vec3(1, 0, 0));
				drona->pos_checkpoint = checkpoints[i + 1]->position;
				ct_checkpoint++;
			}
		}
	}

	// Render the trees
	{
		for (int i = 0; i < brazi.size(); i++) {
			float x = brazi[i]->position.x - drona->position.x;
			float z = brazi[i]->position.z - drona->position.z;
			if (sqrt(x * x + z * z) < dist) {
				RenderMesh(brazi[i]->GetMeshes()[0], shaders["VertexColor"], brazi[i]->GetTransforms()[0]);
				RenderMesh(brazi[i]->GetMeshes()[1], shaders["VertexColor"], brazi[i]->GetTransforms()[1]);
				RenderMesh(brazi[i]->GetMeshes()[2], shaders["VertexColor"], brazi[i]->GetTransforms()[2]);
			}
		}
	}

	{
		for (int i = 0; i < trees.size(); i++) {
			float x = trees[i]->position.x - drona->position.x;
			float z = trees[i]->position.z - drona->position.z;
			if (sqrt(x * x + z * z) < dist) {
				RenderMesh(trees[i]->GetMeshes()[0], shaders["VertexColor"], trees[i]->GetTransforms()[0]);
				RenderMesh(trees[i]->GetMeshes()[1], shaders["VertexColor"], trees[i]->GetTransforms()[1]);
			}
		}
	}

	// Render the buildings
	{
		for (int i = 0; i < buildings.size(); i++) {
			float x = buildings[i]->position.x - drona->position.x;
			float z = buildings[i]->position.z - drona->position.z;
			if (sqrt(x * x + z * z) < dist) {
				RenderMesh(buildings[i]->GetMesh()[0], shaders["VertexColor"], buildings[i]->GetTransforms()[0]);
				RenderMesh(buildings[i]->GetMesh()[1], shaders["VertexColor"], buildings[i]->GetTransforms()[1]);
			}
		}
	}

	// Render the drone
	{
		if (droneType == 1) {
			drona->CreateDrone1();
		}
		else if (droneType == 2) {
			drona->CreateDrone2();
		}
		else if (droneType == 3) {
			drona->CreateDrone3();
		}

		drona->Update(deltaTimeSeconds, droneType, move);

		camera->Set(drona->position + glm::vec3(0, 0, 7), drona->position, glm::vec3(0, 1, 0));
		camera->SetRotation(glm::vec3(glm::radians(drona->rotateX), glm::radians(drona->rotateY), glm::radians(drona->rotateZ)));
		camera->SetDistance(glm::vec3(0, 0, 7));
		camera->move = move;

		drona->propellerRotation += 2 * deltaTimeSeconds;

		vector<Mesh*> meshes;
		vector<glm::mat4> transforms;
		meshes = drona->GetMeshes();
		transforms = drona->GetTransforms();

		for (int i = 0; i < meshes.size(); i++) {
			RenderMesh(meshes[i], shaders["VertexColor"], transforms[i]);
		}
	}

	// timer
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 0.9f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(lungime, 1, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5, 0, 0));
		RenderMeshTimer(meshes["timer"], shaders["VertexColor"], modelMatrix);
		lungime -= deltaTimeSeconds * 0.002f;
		//cout << lungime << endl;
	}

	// minimap
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, 250, 150);

		cameraMiniMap->Set(drona->position + glm::vec3(0, 10, 3.5f), drona->position, glm::vec3(0, 1, 0));

		// Render the drone
		{
			if (droneType == 1) {
				drona->CreateDrone1();
			}
			else if (droneType == 2) {
				drona->CreateDrone2();
			}
			else if (droneType == 3) {
				drona->CreateDrone3();
			}

			drona->Update(deltaTimeSeconds, droneType, move);

			drona->propellerRotation += 2 * deltaTimeSeconds;

			vector<Mesh*> meshes;
			vector<glm::mat4> transforms;
			meshes = drona->GetMeshes();
			transforms = drona->GetTransforms();

			for (int i = 0; i < meshes.size(); i++) {
				RenderSimpleMesh(meshes[i], shaders["VertexColor"], transforms[i], cameraMiniMap);
			}
		}

		// the map
		{
			RenderSimpleMesh(map->GetMesh(), shaders["LabShader"], glm::mat4(1), cameraMiniMap);
		}

		// Render the checkpoints
		{
			for (int i = ct_checkpoint; i < checkpoints.size(); i++) {
				float x = checkpoints[i]->position.x - drona->position.x;
				float z = checkpoints[i]->position.z - drona->position.z;
				if (sqrt(x * x + z * z) < dist) {
					RenderMesh(checkpoints[i]->GetMeshes()[0], shaders["VertexColor"], checkpoints[i]->GetTransforms()[0]);
					RenderMesh(checkpoints[i]->GetMeshes()[1], shaders["VertexColor"], checkpoints[i]->GetTransforms()[1]);
					RenderMesh(checkpoints[i]->GetMeshes()[2], shaders["VertexColor"], checkpoints[i]->GetTransforms()[2]);
				}
				if (checkpoints[i]->IsPassingThrough(drona->position) && ct_checkpoint == i) {
					checkpoints[i + 1]->ChangeMesh(glm::vec3(1, 0, 0));
					drona->pos_checkpoint = checkpoints[i + 1]->position;
					ct_checkpoint++;
				}
			}
		}

		// Render the trees
		{
			for (int i = 0; i < brazi.size(); i++) {
				float x = brazi[i]->position.x - drona->position.x;
				float z = brazi[i]->position.z - drona->position.z;
				if (sqrt(x * x + z * z) < dist) {
					RenderSimpleMesh(brazi[i]->GetMeshes()[0], shaders["VertexColor"], brazi[i]->GetTransforms()[0], cameraMiniMap);
					RenderSimpleMesh(brazi[i]->GetMeshes()[1], shaders["VertexColor"], brazi[i]->GetTransforms()[1], cameraMiniMap);
					RenderSimpleMesh(brazi[i]->GetMeshes()[2], shaders["VertexColor"], brazi[i]->GetTransforms()[2], cameraMiniMap);
				}
			}
		}

		{
			for (int i = 0; i < trees.size(); i++) {
				float x = trees[i]->position.x - drona->position.x;
				float z = trees[i]->position.z - drona->position.z;
				if (sqrt(x * x + z * z) < dist) {
					RenderSimpleMesh(trees[i]->GetMeshes()[0], shaders["VertexColor"], trees[i]->GetTransforms()[0], cameraMiniMap);
					RenderSimpleMesh(trees[i]->GetMeshes()[1], shaders["VertexColor"], trees[i]->GetTransforms()[1], cameraMiniMap);
				}
			}
		}

		// Render the buildings
		{
			for (int i = 0; i < buildings.size(); i++) {
				float x = buildings[i]->position.x - drona->position.x;
				float z = buildings[i]->position.z - drona->position.z;
				if (sqrt(x * x + z * z) < dist) {
					RenderSimpleMesh(buildings[i]->GetMesh()[0], shaders["VertexColor"], buildings[i]->GetTransforms()[0], cameraMiniMap);
					RenderSimpleMesh(buildings[i]->GetMesh()[1], shaders["VertexColor"], buildings[i]->GetTransforms()[1], cameraMiniMap);
				}
			}
		}
	}

	// coliziuni
	{
		for (int i = 0; i < coliziune_obiecte.size(); i++) {
			if (drona->checkCollision(*coliziune_obiecte[i]) == 1) {
				drona->life = 2;
				break;
			}
		}

		for (int i = 0; i < coliziune_checkpoint.size(); i++) {
			if (drona->checkCollision(*coliziune_checkpoint[i]) == 1) {
				drona->life = 2;
				break;
			}
		}
	}
}


void Tema2::FrameEnd() {}


void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Tema2::RenderMeshTimer(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	glm::mat4 orto = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

	glDisable(GL_DEPTH_TEST);

	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(orto));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();

	glEnable(GL_DEPTH_TEST);
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, implemented::Camera_tema* camera)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);

	// Set MVP matrices
	int loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");

	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the mesh
	glBindVertexArray(mesh->GetBuffers()->m_VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		if (move == 0) {
			drona->position.z -= deltaTime * 15;
			for (int i = 0; i < coliziune_obiecte.size(); i++) {
				if (drona->checkCollision(*coliziune_obiecte[i]) == 1) {
					drona->position.z += deltaTime * 15;
					break;
				}
			}
			for (int i = 0; i < coliziune_checkpoint.size(); i++) {
				if (drona->checkCollision(*coliziune_checkpoint[i]) == 1) {
					drona->position.z += deltaTime * 15;
					break;
				}
			}
		}
		else {
			drona->ChangeSpeed(0.05f);
		}
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		if (move == 0) {
			drona->position.x -= deltaTime * 15;
			for (int i = 0; i < coliziune_obiecte.size(); i++) {
				if (drona->checkCollision(*coliziune_obiecte[i]) == 1) {
						drona->position.x += deltaTime * 15;
					break;
				}
			}
			for (int i = 0; i < coliziune_checkpoint.size(); i++) {
				if (drona->checkCollision(*coliziune_checkpoint[i]) == 1) {
					drona->position.x += deltaTime * 15;
					break;
				}
			}
		}
		else {
			drona->rotateY += 20 * deltaTime;
		}
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		if (move == 0) {
			drona->position.z += deltaTime * 15;
			for (int i = 0; i < coliziune_obiecte.size(); i++) {
				if (drona->checkCollision(*coliziune_obiecte[i]) == 1) {
					drona->position.z -= deltaTime * 15;
					break;
				}
			}
			for (int i = 0; i < coliziune_checkpoint.size(); i++) {
				if (drona->checkCollision(*coliziune_checkpoint[i]) == 1) {
					drona->position.z -= deltaTime * 15;
					break;
				}
			}
		}
		else {
			drona->ChangeSpeed(-0.05f);
		}
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		if (move == 0) {
			drona->position.x += deltaTime * 15;
			for (int i = 0; i < coliziune_obiecte.size(); i++) {
				if (drona->checkCollision(*coliziune_obiecte[i]) == 1) {
					drona->position.x -= deltaTime * 15;
					break;
				}
			}
			for (int i = 0; i < coliziune_checkpoint.size(); i++) {
				if (drona->checkCollision(*coliziune_checkpoint[i]) == 1) {
					drona->position.x -= deltaTime * 15;
					break;
				}
			}
		}
		else {
			drona->rotateY -= 20 * deltaTime;
		}
	}

	if (window->KeyHold(GLFW_KEY_Q)) {
		if (move == 0) {
			drona->position.y += deltaTime * 15;
			for (int i = 0; i < coliziune_obiecte.size(); i++) {
				if (drona->checkCollision(*coliziune_obiecte[i]) == 1) {
					drona->position.y -= deltaTime * 15;
					break;
				}
			}
			for (int i = 0; i < coliziune_checkpoint.size(); i++) {
				if (drona->checkCollision(*coliziune_checkpoint[i]) == 1) {
					drona->position.y -= deltaTime * 15;
					break;
				}
			}
		}
	}

	if (window->KeyHold(GLFW_KEY_E)) {
		if (move == 0) {
			drona->position.y -= deltaTime * 15;
			for (int i = 0; i < coliziune_obiecte.size(); i++) {
				if (drona->checkCollision(*coliziune_obiecte[i]) == 1) {
					drona->position.y += deltaTime * 15;
					break;
				}
			}
			for (int i = 0; i < coliziune_checkpoint.size(); i++) {
				if (drona->checkCollision(*coliziune_checkpoint[i]) == 1) {
					drona->position.y += deltaTime * 15;
					break;
				}
			}
		}
	}

	if (window->KeyHold(GLFW_KEY_R) && move == 0) {
		drona->rotateY += 20 * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_T) && move == 0) {
		drona->rotateY -= 20 * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_UP)) {
		drona->rotateX -= 50 * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_DOWN)) {
		drona->rotateX += 50 * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_LEFT)) {
		drona->rotateZ += 50 * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_RIGHT)) {
		drona->rotateZ -= 50 * deltaTime;
	}
}


void Tema2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_P) {
		droneType++;
		if (droneType == 4) droneType = 1;
	}
	if (key == GLFW_KEY_O) {
		move = (move + 1) % 2;
	}
}


void Tema2::OnKeyRelease(int key, int mods)
{
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
