#pragma once
#include <Component/SimpleScene.h>
#include "Transform3D.h"

class Flame
{
public:
	Flame();
	~Flame();

	void Init();
	void Update(float deltaTimeSeconds);
	glm::mat4 modelMatrix;
	float x;
	float y;
	float z;
};
