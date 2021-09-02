#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Bow : public SimpleScene
{
public:
	Bow();
	~Bow();
	void Init() override;
	void Update(float deltaTimeSeconds) override;

public:
	glm::mat3 objMatrix;
	float angle;
	float Y;
	float X;
	float bowSpeed = 4;
	POINT cursor;
};
