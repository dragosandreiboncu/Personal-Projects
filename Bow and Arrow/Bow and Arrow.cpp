#include "Tema1.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <Core/Engine.h>
#include <list>
#include "Object2D.h"
#include "Transform2D.h"
#include "Bow.h"
#include "Arrow.h"
#include "Balloon.h"
#include "Shuriken.h"
#include "Heart.h"

using namespace std;

Tema1::Tema1()
{
}
Tema1::~Tema1()
{
}

void Tema1::Init()
{
	bow.Init();
	// iterate between arrows
	for (int i = 0; i < arrow_nr; i++)
	{
		arrow = new Arrow();
		arrow->Init();
		arrow->getBowCoord(bow.X, bow.Y, bow.angle);
		arrows[i] = *arrow;
	}
	// iterate between balloons
	for (int i = 0; i < balloons_nr; i++)
	{
		balloon = new Balloon();
		balloon->Init();
		balloons[i] = *balloon;
		balloons[i].X = 350 + ((rand() % 8) + (rand() % 9) * 0.1) * 100;
		balloons[i].Y = -((rand() % 4) + (rand() % 9) * 0.1) * 100;
		if (i % 2)
			balloons[i].color = "red_balloon";
		else
			balloons[i].color = "yellow_balloon";
	}
	// iterate between shurikens
	for (int i = 0; i < shuriken_nr; i++)
	{
		shuriken = new Shuriken();
		shuriken->Init();
		shurikens[i] = *shuriken;
		shurikens[i].X = window->GetResolution().x + ((rand() % 4 + (rand() % 9) * 0.1) * 100);
		shurikens[i].Y = 100 + ((rand() % 6) + (rand() % 9) * 0.1) * 100;
		shurikens[i].shurikenRotSpeed = 0.01 + (rand() % 9) * 0.006;
		shurikens[i].shurikenSpeed = 1 + (rand() % 2);
	}
	for (int i = 0; i < heart_nr; i++)
	{
		heart = new Heart();
		heart->Init();
		hearts[i] = *heart;
		hearts[i].X += i * 150;
	}

	cooldownArrow = 1;
	cooldownScore = 5;
	canShoot = true;
	hearts_lost = 0;
	arrow_iter = 0;
	score = 0;
	clickPressed = false;
	clickReleased = false;
}

void Tema1::FrameStart()
{
	glClearColor(0.6, 0.6, 0.6, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	// check if mouse button 1 is released
	if (clickReleased)
	{
		arrows[arrow_iter].launched = true;
		clickReleased = false;
	}
	// checking the cooldown for arrow
	if (cooldownArrow <= 0)
		canShoot = true;
	else
		cooldownArrow -= deltaTimeSeconds;
	// the program shows the score with 5 sec delay
	if (cooldownScore <= 0)
	{
		cout << "Score: ";
		cout << score;
		cout << "\n";
		cooldownScore = 5;
	}
	else
		cooldownScore -= deltaTimeSeconds;

	bow.Update(deltaTimeSeconds);
	// applying cooldown for arrow reload
	if (arrows[arrow_iter].launched)
	{
		cooldownArrow = 1;
		canShoot = false;
		arrow_iter++;
		if (arrow_iter == arrow_nr)
			arrow_iter = 0;
	}
	// iterate between arrows
	for (int i = 0; i < arrow_nr; i++)
	{
		// if arrows are not launched they receive coords from bow
		if (i == arrow_iter && !arrows[i].launched && canShoot)
			arrows[i].getBowCoord(bow.X, bow.Y, bow.angle);
		// if arrows are out of screen, they respawn
		if (arrows[i].X > window->GetResolution().x ||
				arrows[i].Y < -100)
		{
			arrows[i].hitTarget = false;
			arrows[i].launched = false;
			arrows[i].X = 90;
		}
		if ((i == arrow_iter && canShoot) || arrows[i].launched)
		{
			arrows[i].Update(deltaTimeSeconds);
		}
		// check for shuriken collision and applying them
		for (int j = 0; j < shuriken_nr; j++)
		{
			if (collisionDetect(5, 32, arrows[i].realX, shurikens[j].X,
				arrows[i].realY, shurikens[j].Y) && arrows[i].launched &&
				!arrows[i].hitTarget && !shurikens[j].destroyed)
			{
				arrows[i].hitTarget = true;
				shurikens[j].destroyed = true;
				shurikens[j].X++;
				score += scorePerShuriken;
			}
		}
		// check for balloon collision and applying them
		for (int j = 0; j < balloons_nr; j++)
		{
			if ((collisionDetect(5, 20, arrows[i].realX, balloons[j].X, arrows[i].realY, balloons[j].Y + 20) ||
				collisionDetect(5, 20, arrows[i].realX, balloons[j].X,arrows[i].realY, balloons[j].Y - 17))
				&& arrows[i].launched && !arrows[i].hitTarget && !balloons[j].destroyed)
			{
				arrows[i].hitTarget = true;
				balloons[j].destroyed = true;
				balloons[j].Y--;
				balloons[j].balloonSpeed = 1;
				if (balloons[j].color == "red_balloon")
					score += scorePerRedBalloon;
				if (balloons[j].color == "yellow_balloon")
					score += scorePerYellowBalloon;
			}
		}
	}
	// iterate between balloons
	for (int i = 0; i < balloons_nr; i++)
	{
		// random zig zag for balloons
		if (!balloons[i].destroyed && !balloons[i].falling)
		{
			if (i < 3)
				balloons[i].X += (rand() % 2);
			else
				balloons[i].X -= (rand() % 2);
			balloons[i].balloonSpeed = (rand() % 2);
		}
		// if they get out of screen, they respawn
		if (balloons[i].Y > window->GetResolution().y + 100)
		{
			balloons[i].X = 350 + ((rand() % 8) + (rand() % 9) * 0.1) * 100;
			balloons[i].Y = -((rand() % 3) + (rand() % 9) * 0.1) * 100;
		}
		// if balloons pop, their tail is falling
		if (balloons[i].scale == 0) 
		{
			balloons[i].destroyed = false;
			balloons[i].falling = true;
		}
		// if they get out of screen after they are destroyed, they respawn
		if (balloons[i].Y < -50 && balloons[i].falling)
		{
			balloons[i].scale = 23;
			balloons[i].falling = false;
			balloons[i].X = 350 + ((rand() % 8) + (rand() % 9) * 0.1) * 100;
			balloons[i].Y = -((rand() % 3) + (rand() % 9) * 0.1) * 100;
		}
		balloons[i].Update(deltaTimeSeconds);
	}
	// iterate between shurikens
	for (int i = 0; i < shuriken_nr; i++)
	{
		// if shurikens are out of screen, they respawn
		if (shurikens[i].X < 0 || shurikens[i].Y < -100)
		{
			shurikens[i].X = window->GetResolution().x + ((rand() % 4 + (rand() % 9) * 0.1) * 100);
			shurikens[i].Y = 100 + ((rand() % 6) + (rand() % 9) * 0.1) * 100;
			shurikens[i].angle = 0;
			shurikens[i].shurikenRotSpeed = 0.01 + (rand() % 9) * 0.006;
			shurikens[i].shurikenSpeed = 1 + (rand() % 2);
			shurikens[i].destroyed = false;
		}
		shurikens[i].Update(deltaTimeSeconds);
		// check collision with bow and applying them
		if (collisionDetect(80, 32, bow.X, shurikens[i].X, bow.Y + 80, shurikens[i].Y) && !shurikens[i].destroyed)
		{
			shurikens[i].destroyed = true;
			hearts_lost++;
			if (hearts_lost < heart_nr)
			{
				hearts[heart_nr - hearts_lost].losed = true;
				cout << "You have ";
				cout << heart_nr - hearts_lost;
				if (hearts_lost == 1)
					cout << " lifes remaining.";
				if (hearts_lost == 2)
					cout << " life remaining.";
				cout << "\n";
			}
			else
			{
				cout << "GAME OVER!";
				cout << "\n";
				cout << "Final score: ";
				cout << score;
				cout << "\n";
				exit(0);
			}
		}
	}

	for (int i = 0; i < heart_nr; i++)
	{
		hearts[i].Update(deltaTimeSeconds);
	}
}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W))
		if (bow.Y <= 520)
			bow.Y += bow.bowSpeed;
	if (window->KeyHold(GLFW_KEY_S))
		if (bow.Y >= 50)
			bow.Y -= bow.bowSpeed;
	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
	{
		if (canShoot)
		{
			if (arrows[arrow_iter].X > 60)
			{
				arrows[arrow_iter].X -= 0.4;
			}
			arrows[arrow_iter].powerBarOn = true;
			clickPressed = true;
		}
	}
	else if (clickPressed)
	{
		clickReleased = true;
		clickPressed = false;
	}

}

bool Tema1::collisionDetect(float rad1, float rad2, float x1, float x2, float y1, float y2)
{
	float x = x1 - x2;
	float y = y1 - y2;
	float distance = sqrt(x * x + y * y);
	if (distance < rad1 + rad2)
		return true;
	return false;
}
