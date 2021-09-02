#pragma once
#include <Component/SimpleScene.h>
#include "Transform3D.h"

class Boss
{
public:
	Boss();
	~Boss();

	void Init();
	void Update(float deltaTimeSeconds);
	glm::mat4 modelMatrix1;
	glm::mat4 modelMatrix2;
	glm::mat4 modelMatrix3;
	glm::mat4 modelMatrix4;
	glm::mat4 modelMatrix5;
	float boss_x;
	bool reverse;
	bool ball_despawn;
	float ball_z;
	float ball_y;
	float boss_next_x;
};
