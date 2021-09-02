#pragma once
#include <Component/SimpleScene.h>
#include "Transform3D.h"

class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update(float deltaTimeSeconds);
	glm::mat4 modelMatrix;
	float x;
	float y;
	float z;
	float cooldownJump;
	float fuel;
	float score;
	float scale;
	bool thirdPerson;
	bool canJump;
	bool jumpEffect;
	bool onPlatform;
	float rotate;
	float rotateSpeed;
};
