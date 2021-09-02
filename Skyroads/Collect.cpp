#include "Collect.h"
#include <vector>
#include <string>
#include <iostream>
#include <Core/Engine.h>

using namespace std;

Collect::Collect()
{
}

Collect::~Collect()
{
}

void Collect::Init()
{
	modelMatrix = glm::mat4(1);
	x = 0;
	y = 0;
	z = 0;
	rotate = 0;
	goUp = 0;
	goUpBool = true;
	collected = false;
	type = 0;
}

void Collect::Update(float deltaTimeSeconds)
{
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(x, y + goUp, z);
	if (type == 0)
		modelMatrix *= Transform3D::RotateOY(rotate);
	if (type == 1)
		modelMatrix *= Transform3D::RotateOX(rotate);
	if (type == 2)
		modelMatrix *= Transform3D::RotateOZ(rotate);
	modelMatrix *= Transform3D::Scale(0.75, 0.75, 0.75);

	if (goUpBool)
		goUp += 0.01;
	else
		goUp -= 0.01;
	if (goUp > 1)
		goUpBool = false;
	if (goUp <= 0)
		goUpBool = true;
	rotate += 0.025;
}