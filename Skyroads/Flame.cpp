#include "Flame.h"
#include <vector>
#include <string>
#include <iostream>
#include <Core/Engine.h>

using namespace std;

Flame::Flame()
{
}

Flame::~Flame()
{
}

void Flame::Init()
{
	x = 0;
	y = 0;
	z = 0;
}

void Flame::Update(float deltaTimeSeconds)
{
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(x, y, z);
	modelMatrix *= Transform3D::Scale(1.25, 0.65, 0.1);
}