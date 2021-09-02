#pragma once
#include <Component/SimpleScene.h>
#include <string>
#include "Tema3Camera.h"
#include "Player.h"
#include "Platform.h"
#include "Object3D.h"
#include "Fuel.h"
#include "Boss.h"
#include "Skull.h"
#include "Flame.h"
#include "Collect.h"
#include "Transform3D.h"
#include "Transform2D.h"

using namespace std;

class Tema3 : public SimpleScene
{
public:
	Tema3();
	~Tema3();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;
	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4 &modelMatrix, Texture2D* texture1 = NULL);
	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	bool CheckCollision(float x1, float y1, float z1, float scale1, float x2, float y2, float z2, float scaleX2, float scaleY2, float scaleZ2);

protected:
	Tema3Camera::Camera* camera;
	glm::mat4 projectionMatrix;
	Player player;
	Fuel fuel;
	Platform platforms[8][3];
	Platform* platform;
	int platforms_nr = 8;
	int platforms_columns = 3;
	string colors[8];
	float platforms_speed;
	Platform* lastPlatform;
	string lastPlatformColor;
	bool orangeEffect;
	float orangeEffectCountdown;
	float speedBeforeOrangeEffect;
	float scoreCountdown;
	float shaderVariety;
	string player_type;
	int life_nr;
	int life_max = 3;
	Boss boss;
	bool ball_damaged;
	unordered_map<std::string, Texture2D*> Textures;
	Skull* skull;
	Skull skulls[6];
	int skulls_nr = 6;
	Collect* collect;
	Collect collects[4];
	int collects_nr = 4;
	Flame* flame;
	Flame flames[4];
	int flames_nr = 4;
};
