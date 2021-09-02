#include "Player.h"
#include <vector>
#include <string>
#include <iostream>
#include <Core/Engine.h>

using namespace std;

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	modelMatrix = glm::mat4(1);
	x = 0;
	y = 0;
	z = -0.25;
	thirdPerson = true;
	jumpEffect = false;
	canJump = true;
	onPlatform = false;
	cooldownJump = 0;
	fuel = 100;
	score = 0;
	scale = 0.4;
	rotate = 0;
	rotateSpeed = 0;
}

void Player::Update(float deltaTimeSeconds)
{
	fuel -= 0.01;
	rotate -= rotateSpeed;
	if (y < -0.5)
		scale += 0.04;
	if (fuel <= 0)
	{
		cout << "You ran out of fuel!" << endl;
		cout << "GAME OVER!" << endl;
		cout << "Final score: " << score << endl;
		exit(1);
	}
	if (jumpEffect)
	{
		if(scale > 0.15)
		scale -= 0.008;
		y += 0.06;
	}
	if (y > 3 || cooldownJump <= 0)
		jumpEffect = false;
	// gravity
	if (!onPlatform)
	{
		if(!jumpEffect && scale < 0.7)
			scale += 0.002;
		y -= 0.025;
		canJump = false;
	}
	else
		canJump = true;
	cooldownJump -= deltaTimeSeconds;

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(x, y, z);
	modelMatrix *= Transform3D::RotateOX(rotate);
	modelMatrix *= Transform3D::Scale(scale, 0.4, 0.4);
}