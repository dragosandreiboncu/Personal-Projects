#include "Balloon.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <Core/Engine.h>
#include "Object2D.h"
#include "Transform2D.h"
#include "Tema1.h"

using namespace std;

Balloon::Balloon()
{
}
Balloon::~Balloon()
{
}

void Balloon::Init()
{

	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	Mesh* line3 = Object2D::CreateSquare("balloon_line", glm::vec3(0, 0, 0), 1, glm::vec3(1, 1, 1), true);
	AddMeshToList(line3);
	Mesh* circle2 = Object2D::CreateCircle("red_balloon", glm::vec3(1, 0, 0));
	AddMeshToList(circle2);
	Mesh* circle3 = Object2D::CreateCircle("yellow_balloon", glm::vec3(1, 1, 0));
	AddMeshToList(circle3);

	X = 0;
	Y = 0;
	scale = 23;
	destroyed = false;
	falling = false;
	color = "red_balloon";
	balloonSpeed = 1;
}
void Balloon::Update(float deltaTimeSeconds)
{
	// if balloons are destroyed, they pop
	if(destroyed)
		scale--;
	if (!falling)
	{
		if(!destroyed)
			Y += balloonSpeed;
		objMatrix = glm::mat3(1);
		objMatrix *= Transform2D::Translate(X, Y);
		objMatrix *= Transform2D::Scale(scale, scale * 2);
		RenderMesh2D(meshes[color], shaders["VertexColor"], objMatrix);
	}
	// if balloons are destroyed, they are falling after they pop
	if(falling && !destroyed)
		Y -= balloonSpeed;
	objMatrix = glm::mat3(1);
	objMatrix *= Transform2D::Translate(X + 4, Y - 55);
	objMatrix *= Transform2D::Rotate(DegreeInRad90 / 3);
	objMatrix *= Transform2D::Translate(-X - 4, -Y + 55);;
	objMatrix *= Transform2D::Translate(X + 4, Y - 55);
	objMatrix *= Transform2D::Scale(2, 13);
	RenderMesh2D(meshes["balloon_line"], shaders["VertexColor"], objMatrix);
	objMatrix = glm::mat3(1);
	objMatrix *= Transform2D::Translate(X - 4, Y - 62);
	objMatrix *= Transform2D::Rotate(-DegreeInRad90 / 2);
	objMatrix *= Transform2D::Translate(-X + 4, -Y + 62);;
	objMatrix *= Transform2D::Translate(X - 4, Y - 62);
	objMatrix *= Transform2D::Scale(2, 13);
	RenderMesh2D(meshes["balloon_line"], shaders["VertexColor"], objMatrix);
	objMatrix = glm::mat3(1);
	objMatrix *= Transform2D::Translate(X + 1, Y - 75);
	objMatrix *= Transform2D::Rotate(DegreeInRad90 / 3);
	objMatrix *= Transform2D::Translate(-X - 1, -Y + 75);;
	objMatrix *= Transform2D::Translate(X + 1, Y - 75);
	objMatrix *= Transform2D::Scale(2, 13);
	RenderMesh2D(meshes["balloon_line"], shaders["VertexColor"], objMatrix);
}

