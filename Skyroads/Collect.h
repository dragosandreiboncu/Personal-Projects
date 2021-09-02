#pragma once
#include <Component/SimpleScene.h>
#include "Transform3D.h"

class Collect
{
public:
	Collect();
	~Collect();

	void Init();
	void Update(float deltaTimeSeconds);
	glm::mat4 modelMatrix;
	float x;
	float y;
	float z;
	float goUp;
	float rotate;
	bool collected;
	int type;
	bool goUpBool;
};
