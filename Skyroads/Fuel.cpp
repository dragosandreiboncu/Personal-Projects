#include "Fuel.h"
#include <vector>
#include <string>
#include <iostream>
#include <Core/Engine.h>
#include "Transform2D.h"

using namespace std;

Fuel::Fuel()
{
}

Fuel::~Fuel()
{
}

void Fuel::Init()
{
	modelMatrix1 = glm::mat3(1);
	modelMatrix2 = glm::mat3(1);
	x = 40;
	y = 680;
	scaleX = 200;
}

void Fuel::Update(float deltaTimeSeconds)
{
	modelMatrix1 = glm::mat3(1);
	modelMatrix1 *= Transform2D::Translate(x - 2, y - 2);
	modelMatrix1 *= Transform2D::Scale(204, 34);

	modelMatrix2 = glm::mat3(1);
	modelMatrix2 *= Transform2D::Translate(x, y);
	modelMatrix2 *= Transform2D::Scale(scaleX, 30);
}