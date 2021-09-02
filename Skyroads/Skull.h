#pragma once
#include <Component/SimpleScene.h>
#include "Transform3D.h"

class Skull
{
public:
	Skull();
	~Skull();

	void Init();
	void Update(float deltaTimeSeconds);
	glm::mat4 modelMatrix1;
	glm::mat4 modelMatrix2;
	glm::mat4 modelMatrix3;
	glm::mat4 modelMatrix4;
	glm::mat4 modelMatrix5;
	glm::mat4 modelMatrix6;
	glm::mat4 modelMatrix7;
	glm::mat4 modelMatrix8;
	float x;
	float y;
	float z;
	float scale;
};
