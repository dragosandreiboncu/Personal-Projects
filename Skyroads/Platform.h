#pragma once
#include <string>
#include <Component/SimpleScene.h>
#include "Transform3D.h"
using namespace std;

class Platform
{
public:
	Platform();
	~Platform();

	void Init();
	void Update(float deltaTimeSeconds);
	glm::mat4 modelMatrix;
	float x;
	float y;
	float z;
	float speed;
	float scale;
	float height = 0.25;
	float width = 1.5;
	string color;
};
