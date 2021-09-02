#include "Arrow.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <Core/Engine.h>
#include "Object2D.h"
#include "Transform2D.h"
#include "Tema1.h"

using namespace std;

Arrow::Arrow()
{
}
Arrow::~Arrow()
{
}

void Arrow::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	X = 90;
	Y = 0;
	bowX = 0;
	bowY = 0;
	realY = 0;
	realX = 0;
	angle = 0;
	launched = false;
	arrowSpeed = 3;
	powerBarOn = false;
	hitTarget = false;

	Mesh* line2 = Object2D::CreateSquare("arrow_line", glm::vec3(0, 0, 0), 1, glm::vec3(0, 0, 0), true);
	AddMeshToList(line2);
	Mesh* triangle1 = Object2D::CreateTriangle("arrow_head", 1, glm::vec3(0, 0, 1), true);
	AddMeshToList(triangle1);

	Mesh* square1 = Object2D::CreateSquare("power_bar", glm::vec3(0, 0, 0), 1, glm::vec3(0, 0, 0), false);
	AddMeshToList(square1);
	Mesh* square2 = Object2D::CreateSquare("power_bar_fill", glm::vec3(0, 0, 0), 1, glm::vec3(0, 1, 0), true);
	AddMeshToList(square2);
}
void Arrow::Update(float deltaTimeSeconds)
{
	// if arrows hit something, they are falling
	if (hitTarget)
		Y-= 4;
	else
	if (launched && !hitTarget)
	{
		// after the arrows are launched, they are going straight
		realY += (sin(angle) * arrowSpeed); 
		realX += (cos(angle) * arrowSpeed);
		X += arrowSpeed;
		powerBarOn = false;
	}
	if (!launched)
	{
		Y = bowY + 80;
		arrowSpeed = 3 + ((90 - X) / 5);
		realY += 85 * sin(angle) - sin(angle) * (90 - X);
		realX += 85 * cos(angle) - cos(angle) * (90 - X) + 10;
	}
	objMatrix = glm::mat3(1);
	objMatrix *= Transform2D::Translate(bowX, Y);
	objMatrix *= Transform2D::Rotate(angle);
	objMatrix *= Transform2D::Translate(-bowX, -Y);
	objMatrix *= Transform2D::Translate(X, Y);
	objMatrix *= Transform2D::Scale(90, 2);
	RenderMesh2D(meshes["arrow_line"], shaders["VertexColor"], objMatrix);
	objMatrix = glm::mat3(1);
	objMatrix *= Transform2D::Translate(bowX, Y);
	objMatrix *= Transform2D::Rotate(angle);
	objMatrix *= Transform2D::Translate(-bowX, -Y);
	objMatrix *= Transform2D::Translate(X + 89, Y - 9);
	objMatrix *= Transform2D::Scale(20, 20);
	RenderMesh2D(meshes["arrow_head"], shaders["VertexColor"], objMatrix);
	if (powerBarOn)
	{
		objMatrix = glm::mat3(1);
		objMatrix *= Transform2D::Translate(bowX - 20, bowY - 50);
		objMatrix *= Transform2D::Scale(60, 10);
		RenderMesh2D(meshes["power_bar"], shaders["VertexColor"], objMatrix);
		objMatrix = glm::mat3(1);
		objMatrix *= Transform2D::Translate(bowX - 20, bowY - 50);
		objMatrix *= Transform2D::Scale((90 - X) * 2, 10);
		RenderMesh2D(meshes["power_bar_fill"], shaders["VertexColor"], objMatrix);
	}
}
void Arrow::getBowCoord(float bow_X, float bow_Y, float bow_angle)
{
	realX = bow_X - 10;
	realY = bow_Y + 80;
	bowX = bow_X;
	bowY = bow_Y;
	angle = bow_angle;
}


