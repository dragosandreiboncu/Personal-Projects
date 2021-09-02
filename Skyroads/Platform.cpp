#include "Platform.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Platform::Platform()
{
}

Platform::~Platform()
{
}

void Platform::Init()
{
	modelMatrix = glm::mat4(1);
	x = 0;
	y = -0.25;
	z = -2.25;
	speed = 0.025;
	scale = 1;
	color = "platformBlue";
}

void Platform::Update(float deltaTimeSeconds)
{
	z += speed;
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(x, y, z);
	modelMatrix *= Transform3D::Scale(width, height, scale);
}