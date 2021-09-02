#include "Skull.h"
#include <vector>
#include <string>
#include <iostream>
#include <Core/Engine.h>

using namespace std;

Skull::Skull()
{
}

Skull::~Skull()
{
}

void Skull::Init()
{
	modelMatrix1 = glm::mat4(1);
	modelMatrix2 = glm::mat4(1);
	modelMatrix3 = glm::mat4(1);
	modelMatrix4 = glm::mat4(1);
	modelMatrix5 = glm::mat4(1);
	modelMatrix6 = glm::mat4(1);
	modelMatrix7 = glm::mat4(1);
	modelMatrix8 = glm::mat4(1);
	x = 0;
	y = 0;
	z = 0;
	scale = 1;
}

void Skull::Update(float deltaTimeSeconds)
{
	modelMatrix1 = glm::mat4(1);
	modelMatrix1 *= Transform3D::Translate(x, y, z);
	modelMatrix1 *= Transform3D::Scale(0.5 * scale, 0.5 * scale, 0.01);

	modelMatrix2 = glm::mat4(1);
	modelMatrix2 *= Transform3D::Translate(x + 0.2 * scale, y + 0.75 * scale, z + 0.02 * scale);
	modelMatrix2 *= Transform3D::RotateOZ(-1.57);
	modelMatrix2 *= Transform3D::Scale(0.25 * scale, 0.35 * scale, 0.01);

	modelMatrix3 = glm::mat4(1);
	modelMatrix3 *= Transform3D::Translate(x - 0.2 * scale, y + 0.75 * scale, z + 0.02 * scale);
	modelMatrix3 *= Transform3D::RotateOZ(1.57);
	modelMatrix3 *= Transform3D::Scale(0.25 * scale, 0.35 * scale, 0.01);

	modelMatrix4 = glm::mat4(1);
	modelMatrix4 *= Transform3D::Translate(x - 0.22 * scale, y - 0.05, z + 0.02 * scale);
	modelMatrix4 *= Transform3D::Scale(0.05 * scale, 0.35 * scale, 0.01);

	modelMatrix5 = glm::mat4(1);
	modelMatrix5 *= Transform3D::Translate(x - 0.02 * scale, y - 0.05, z + 0.02 * scale);
	modelMatrix5 *= Transform3D::Scale(0.05 * scale, 0.35 * scale, 0.01);

	modelMatrix6 = glm::mat4(1);
	modelMatrix6 *= Transform3D::Translate(x + 0.18 * scale, y - 0.05, z + 0.02 * scale);
	modelMatrix6 *= Transform3D::Scale(0.05 * scale, 0.35 * scale, 0.01);

	modelMatrix7 = glm::mat4(1);
	modelMatrix7 *= Transform3D::Translate(9, 3, z + 15);
	modelMatrix7 *= Transform3D::RotateOX(1.57);
	modelMatrix7 *= Transform3D::RotateOY(0.52);
	modelMatrix7 *= Transform3D::Scale(0.3, 0.3, 1.5);

	modelMatrix8 = glm::mat4(1);
	modelMatrix8 *= Transform3D::Translate(-9, 3, z + 15);
	modelMatrix8 *= Transform3D::RotateOX(1.57);
	modelMatrix8 *= Transform3D::RotateOY(-0.52);
	modelMatrix8 *= Transform3D::Scale(0.3, 0.3, 1.5);

	z += 0.05;
}