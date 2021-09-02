#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Arrow : public SimpleScene
{
public:
	Arrow();
	~Arrow();
	void Init() override;
	void Update(float deltaTimeSeconds) override;
	void getBowCoord(float X, float Y, float angle);

public:
	glm::mat3 objMatrix;
	float angle;
	float Y;
	float X;
	float bowX;
	float bowY;
	float realY;
	float realX;
	float arrowSpeed;
	bool launched;
	bool powerBarOn;
	bool hitTarget;
};
