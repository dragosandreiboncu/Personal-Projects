#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Bow.h"
#include "Arrow.h"
#include "Balloon.h"
#include "Shuriken.h"
#include "Heart.h"
#include <iostream>
#include <vector>

using namespace std;

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;
	void OnInputUpdate(float deltaTime, int mods) override;
	bool collisionDetect(float rad1, float rad2, float x1, float x2, float y1, float y2);

protected:
	Bow bow;
	Arrow *arrow;
	Balloon* balloon;
	Shuriken* shuriken;
	Heart *heart;
	Arrow arrows[7];
	Balloon balloons[6];
	Shuriken shurikens[6];
	Heart hearts[3];
	glm::mat3 objMatrix;
	int arrow_nr = 7;
	int balloons_nr = 6;
	int shuriken_nr = 6;
	int heart_nr = 3;
	int hearts_lost;
	int arrow_iter;
	float cooldownArrow;
	bool canShoot;
	int score;
	int scorePerRedBalloon = 5;
	int scorePerYellowBalloon = -1;
	int scorePerShuriken = 1;
	bool clickReleased;
	bool clickPressed;
	float cooldownScore;
};
