#include "Shuriken.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <Core/Engine.h>
#include "Object2D.h"
#include "Transform2D.h"
#include "Tema1.h"

using namespace std;

Shuriken::Shuriken()
{
}
Shuriken::~Shuriken()
{
}

void Shuriken::Init()
{

	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	Mesh* triangle2 = Object2D::CreateTriangle("shuriken", 1, glm::vec3(0, 0, 0), true);
	AddMeshToList(triangle2);

	X = 1400;
	Y = 200;
	angle = 0;
	shurikenRotSpeed = 0.01;
	shurikenSpeed = 2;
	destroyed = false;
}

void Shuriken::Update(float deltaTimeSeconds)
{
	if (!destroyed)
	{
		X -= shurikenSpeed;
		angle += shurikenRotSpeed;
	}
	// if shuriken are destroyed, they are falling
	else
		Y -= 4;
	objMatrix = glm::mat3(1);
	objMatrix *= Transform2D::Translate(X, Y);
	objMatrix *= Transform2D::Rotate(angle);
	objMatrix *= Transform2D::Translate(-X, -Y);
	objMatrix *= Transform2D::Translate(X, Y);
	objMatrix *= Transform2D::Scale(20, 40);
	RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], objMatrix);
	objMatrix = glm::mat3(1);
	objMatrix *= Transform2D::Translate(X, Y);
	objMatrix *= Transform2D::Rotate(angle + DegreeInRad90);
	objMatrix *= Transform2D::Translate(-X, -Y);
	objMatrix *= Transform2D::Translate(X, Y);
	objMatrix *= Transform2D::Scale(20, 40);
	RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], objMatrix);
	objMatrix = glm::mat3(1);
	objMatrix *= Transform2D::Translate(X, Y);
	objMatrix *= Transform2D::Rotate(angle + DegreeInRad90 * 2);
	objMatrix *= Transform2D::Translate(-X, -Y);
	objMatrix *= Transform2D::Translate(X, Y);
	objMatrix *= Transform2D::Scale(20, 40);
	RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], objMatrix);
	objMatrix = glm::mat3(1);
	objMatrix *= Transform2D::Translate(X, Y);
	objMatrix *= Transform2D::Rotate(angle + DegreeInRad90 * 3);
	objMatrix *= Transform2D::Translate(-X, -Y);
	objMatrix *= Transform2D::Translate(X, Y);
	objMatrix *= Transform2D::Scale(20, 40);
	RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], objMatrix);
}

