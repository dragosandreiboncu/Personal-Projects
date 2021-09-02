#include "Heart.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <Core/Engine.h>
#include "Object2D.h"
#include "Transform2D.h"
#include "Tema1.h"

using namespace std;

Heart::Heart()
{
}
Heart::~Heart()
{
}

void Heart::Init()
{

	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	X = (window->GetResolution().x / 2) - 170;
	Y = window->GetResolution().y - 80;
	losed = false;

	Mesh* triangle3 = Object2D::CreateHeart("heart", glm::vec3(1, 0, 0));
	AddMeshToList(triangle3);
}
void Heart::Update(float deltaTimeSeconds)
{
	if (!losed)
	{
		objMatrix = glm::mat3(1);
		objMatrix *= Transform2D::Translate(X, Y);
		objMatrix *= Transform2D::Scale(40, 40);
		RenderMesh2D(meshes["heart"], shaders["VertexColor"], objMatrix);
	}


}


