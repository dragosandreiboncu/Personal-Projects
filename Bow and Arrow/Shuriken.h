#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

using namespace std;

class Shuriken : public SimpleScene
{
public:
	Shuriken();
	~Shuriken();
	void Init() override;
	void Update(float deltaTimeSeconds) override;

public:
	glm::mat3 objMatrix;
	float Y;
	float X;
	float angle;
	float shurikenSpeed;
	float shurikenRotSpeed;
	float DegreeInRad90 = 1.57;
	bool destroyed;
};
