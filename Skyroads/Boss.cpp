#include "Boss.h"
#include <vector>
#include <string>
#include <iostream>
#include <Core/Engine.h>

using namespace std;

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::Init()
{
	modelMatrix1 = glm::mat4(1);
	modelMatrix2 = glm::mat4(1);
	modelMatrix3 = glm::mat4(1);
	modelMatrix4 = glm::mat4(1);
	modelMatrix5 = glm::mat4(1);

	boss_x = -3;
	reverse = false;
	ball_despawn = true;
	ball_z = -68;
	ball_y = 0.75;
	boss_next_x = -2;
}

void Boss::Update(float deltaTimeSeconds)
{
	modelMatrix1 = glm::mat4(1);
	modelMatrix1 *= Transform3D::Translate(boss_x, 1.5, -70);
	modelMatrix1 *= Transform3D::Scale(8, 8, 0.2);

	modelMatrix2 = glm::mat4(1);
	modelMatrix2 *= Transform3D::Translate(boss_x - 1, 3.5, -69);
	modelMatrix2 *= Transform3D::RotateOZ(1.57);
	modelMatrix2 *= Transform3D::Scale(1, 1.5, 0.1);

	modelMatrix3 = glm::mat4(1);
	modelMatrix3 *= Transform3D::Translate(boss_x + 1, 3.5, -69);
	modelMatrix3 *= Transform3D::RotateOZ(-1.57);
	modelMatrix3 *= Transform3D::Scale(1, 1.5, 0.1);

	modelMatrix5 = glm::mat4(1);
	modelMatrix5 *= Transform3D::Translate(boss_x, ball_y, -69);
	modelMatrix5 *= Transform3D::Scale(1.5, 0.5, 0.1);

	if (!reverse && ball_despawn)
		boss_x += 0.01;
	else if (reverse && ball_despawn)
		boss_x -= 0.01;
	if (boss_x >= 3.5)
	{
		reverse = true;
		boss_next_x = 2;
	}
	if (boss_x <= -3.5)
	{
		reverse = false;
		boss_next_x = -2;
	}
	if (ball_z > 3)
	{
		ball_despawn = true;
		ball_z = -68;
		ball_y = -0.1 + (rand() % 2);
	}
	if (boss_x > boss_next_x && !reverse)
	{
		ball_despawn = false;
		boss_next_x++;
	}
	if (boss_x < boss_next_x && reverse)
	{
		ball_despawn = false;
		boss_next_x--;
	}

	if (!ball_despawn)
	{
		modelMatrix4 = glm::mat4(1);
		modelMatrix4 *= Transform3D::Translate(boss_x, ball_y, ball_z);
		modelMatrix4 *= Transform3D::Scale(0.8, 0.8, 0.8);
		ball_z += 0.5;
	}
}