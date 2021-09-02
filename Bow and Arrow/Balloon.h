#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

using namespace std;

class Balloon : public SimpleScene
{
public:
	Balloon();
	~Balloon();
	void Init() override;
	void Update(float deltaTimeSeconds) override;

public:
	glm::mat3 objMatrix;
	float Y;
	float X;
	float balloonSpeed;
	float DegreeInRad90 = 1.57;
	float scale;
	bool falling;
	bool destroyed;
	string color;
};
