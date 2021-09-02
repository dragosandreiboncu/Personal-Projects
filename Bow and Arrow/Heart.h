#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

using namespace std;

class Heart : public SimpleScene
{
public:
	Heart();
	~Heart();
	void Init() override;
	void Update(float deltaTimeSeconds) override;

public:
	glm::mat3 objMatrix;
	bool losed;
	float Y;
	float X;
	float DegreeInRad90 = 1.57;
};
