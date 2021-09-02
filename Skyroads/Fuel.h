#pragma once
#include <Component/SimpleScene.h>
#include "Transform2D.h"

class Fuel
{
public:
	Fuel();
	~Fuel();

	void Init();
	void Update(float deltaTimeSeconds);
	glm::mat3 modelMatrix1;
	glm::mat3 modelMatrix2;
	float x;
	float y;
	float scaleX;
};
