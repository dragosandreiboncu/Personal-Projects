#include "Bow.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <Core/Engine.h>
#include "Object2D.h"
#include "Transform2D.h"
#include "Tema1.h"
using namespace std;
Bow::Bow()
{
}
Bow::~Bow()
{
}

void Bow::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	X = 100;
	Y = 295;
	angle = 0;

	Mesh* line1 = Object2D::CreateSquare("bow_line1", glm::vec3(0, 0, 0), 1, glm::vec3(0.8, 0.5, 0.15), true);
	AddMeshToList(line1);
	Mesh* circle1 = Object2D::CreateHalfCircle("bow_line2", glm::vec3(0.85, 0.85, 0.85));
	AddMeshToList(circle1);
}

void Bow::Update(float deltaTimeSeconds)
{
	// bow is looking for the cursor
	GetCursorPos(&cursor);
	angle = -atan2(cursor.y - (window->GetResolution().y - Y) - 80, cursor.x - X);
	if (angle > 1)
		angle = 1;
	if (angle < -1)
		angle = -1;

	objMatrix = glm::mat3(1);
	objMatrix *= Transform2D::Translate(X, Y + 80);
	objMatrix *= Transform2D::Rotate(angle);
	objMatrix *= Transform2D::Translate(-X, -Y - 80);
	objMatrix *= Transform2D::Translate(X, Y);
	objMatrix *= Transform2D::Scale(3, 160);
	RenderMesh2D(meshes["bow_line1"], shaders["VertexColor"], objMatrix);
	objMatrix = glm::mat3(1);
	objMatrix *= Transform2D::Translate(X + 2, Y + 80);
	objMatrix *= Transform2D::Rotate(angle);
	objMatrix *= Transform2D::Translate(-X - 2, -Y - 80);
	objMatrix *= Transform2D::Translate(X + 2, Y + 80);
	objMatrix *= Transform2D::Scale(1, 3);
	RenderMesh2D(meshes["bow_line2"], shaders["VertexColor"], objMatrix);
}

