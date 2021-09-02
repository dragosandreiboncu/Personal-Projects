#include "Tema3.h"

#include <vector>
#include <string>
#include <iostream>
#include "Tema3Camera.h"
#include <Core/Engine.h>

using namespace std;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
	Mesh* mesh1 = new Mesh("player");
	mesh1->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	AddMeshToList(mesh1);
	Mesh* mesh2 = Object3D::CreatePlatformBox("platformBlue", glm::vec3(0, 0, 0.9), true); // blue
	AddMeshToList(mesh2);
	colors[0] = "platformBlue";
	Mesh* mesh3 = Object3D::CreatePlatformBox("platformRed", glm::vec3(0.9, 0, 0), true); // red
	AddMeshToList(mesh3);
	colors[1] = "platformRed";
	Mesh* mesh4 = Object3D::CreatePlatformBox("platformGreen", glm::vec3(0, 0.9, 0), true); // green
	AddMeshToList(mesh4);
	colors[2] = "platformGreen";
	Mesh* mesh5 = Object3D::CreatePlatformBox("platformYellow", glm::vec3(0.9, 0.9, 0), true); // yellow
	AddMeshToList(mesh5);
	colors[3] = "platformYellow";
	Mesh* mesh6 = Object3D::CreatePlatformBox("platformOrange", glm::vec3(0.9, 0.4, 0), true); // orange
	AddMeshToList(mesh6);
	colors[4] = "platformOrange";
	Mesh* mesh7 = Object3D::CreatePlatformBox("platformBlack", glm::vec3(0, 0, 0), true); // black
	AddMeshToList(mesh7);
	colors[5] = "platformBlack";
	Mesh* mesh8 = Object3D::CreatePlatformBox("platformWhite", glm::vec3(0.95, 0.95, 0.95), true); // white
	AddMeshToList(mesh8);
	colors[6] = "platformWhite";
	Mesh* mesh9 = Object3D::CreatePlatformBox("platformViolet", glm::vec3(0.15, 0, 0.8), true); // violet
	AddMeshToList(mesh9);
	colors[7] = "platformViolet";
	Mesh* mesh10 = Object3D::CreateBar("fuel_bar", glm::vec3(0, 0.75, 0), true);
	AddMeshToList(mesh10);
	Mesh* mesh11 = Object3D::CreateBar("fuel_backgr", glm::vec3(0, 0, 0), true);
	AddMeshToList(mesh11);
	Mesh* mesh12 = Object3D::CreateHeart("heart", glm::vec3(0.9, 0, 0));
	AddMeshToList(mesh12);
	Mesh* mesh13 = new Mesh("boss");
	mesh13->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	AddMeshToList(mesh13);
	Mesh* mesh14 = Object3D::CreateBoss("boss_eye", glm::vec3(0.9, 0, 0), true); // boss_eye
	AddMeshToList(mesh14);
	Mesh* mesh15 = new Mesh("boss_ball");
	mesh15->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	AddMeshToList(mesh15);
	Mesh* mesh16 = Object3D::CreateSkull("skull", glm::vec3(0.9, 0.9, 0.9));
	AddMeshToList(mesh16);
	Mesh* mesh17 = Object3D::CreateBar("skull_teeth", glm::vec3(0.05, 0.05, 0.05), true);
	AddMeshToList(mesh17);
	Mesh* mesh18 = Object3D::CreateFlame("flame", glm::vec3(0.05, 0.05, 0.05));
	AddMeshToList(mesh18);
	Mesh* mesh19 = new Mesh("collect");
	mesh19->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	AddMeshToList(mesh19);
	Mesh* mesh20 = Object3D::CreatePickaxe("pickaxe_handler", glm::vec3(0.96, 0.5, 0.3), true);
	AddMeshToList(mesh20);
	Mesh* mesh21 = Object3D::CreatePickaxe("pickaxe", glm::vec3(0.5, 1, 0.82), true);
	AddMeshToList(mesh21);
	Mesh* mesh22 = new Mesh("background");
	mesh22->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	AddMeshToList(mesh22);


	Shader* shader = new Shader("Player1");
	shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader1.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader1.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	shader = new Shader("Player2");
	shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader2.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader2.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	shader = new Shader("Boss_ball");
	shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader3.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader3.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	shader = new Shader("Texture");
	shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader4.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader4.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	shader = new Shader("Flame");
	shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader5.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader5.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	Texture2D* texture1 = new Texture2D();
	texture1->Load2D("Source/Laboratoare/Tema3/Textures/skull.jpg", GL_REPEAT);
	Textures["skull"] = texture1;

	Texture2D* texture2 = new Texture2D();
	texture2->Load2D("Source/Laboratoare/Tema3/Textures/cobblestoneBlue.jpg", GL_REPEAT);
	Textures["platformBlue"] = texture2;
	Texture2D* texture3 = new Texture2D();
	texture3->Load2D("Source/Laboratoare/Tema3/Textures/cobblestoneViolet.jpg", GL_REPEAT);
	Textures["platformViolet"] = texture3;
	Texture2D* texture4 = new Texture2D();
	texture4->Load2D("Source/Laboratoare/Tema3/Textures/cobblestoneWhite.jpg", GL_REPEAT);
	Textures["platformWhite"] = texture4;
	Texture2D* texture5 = new Texture2D();
	texture5->Load2D("Source/Laboratoare/Tema3/Textures/cobblestoneBlack.jpg", GL_REPEAT);
	Textures["platformBlack"] = texture5;
	Texture2D* texture6 = new Texture2D();
	texture6->Load2D("Source/Laboratoare/Tema3/Textures/cobblestoneRed.jpg", GL_REPEAT);
	Textures["platformRed"] = texture6;
	Texture2D* texture7 = new Texture2D();
	texture7->Load2D("Source/Laboratoare/Tema3/Textures/cobblestoneOrange.jpg", GL_REPEAT);
	Textures["platformOrange"] = texture7;
	Texture2D* texture8 = new Texture2D();
	texture8->Load2D("Source/Laboratoare/Tema3/Textures/cobblestoneGreen.jpg", GL_REPEAT);
	Textures["platformGreen"] = texture8;
	Texture2D* texture9 = new Texture2D();
	texture9->Load2D("Source/Laboratoare/Tema3/Textures/cobblestoneYellow.jpg", GL_REPEAT);
	Textures["platformYellow"] = texture9;
	Texture2D* texture10 = new Texture2D();
	texture10->Load2D("Source/Laboratoare/Tema3/Textures/ball.jpg", GL_REPEAT);
	Textures["player"] = texture10;
	Texture2D* texture11 = new Texture2D();
	texture11->Load2D("Source/Laboratoare/Tema3/Textures/boss_ball.jfif", GL_REPEAT);
	Textures["boss_ball"] = texture11;
	Texture2D* texture12 = new Texture2D();
	texture12->Load2D("Source/Laboratoare/Tema3/Textures/flame.jpg", GL_REPEAT);
	Textures["flame"] = texture12;
	Texture2D* texture13 = new Texture2D();
	texture13->Load2D("Source/Laboratoare/Tema3/Textures/torch.png", GL_REPEAT);
	Textures["torch"] = texture13;
	Texture2D* texture14 = new Texture2D();
	texture14->Load2D("Source/Laboratoare/Tema3/Textures/diamond.png", GL_REPEAT);
	Textures["diamond"] = texture14;
	Texture2D* texture15 = new Texture2D();
	texture15->Load2D("Source/Laboratoare/Tema3/Textures/emerald.png", GL_REPEAT);
	Textures["emerald"] = texture15;
	Texture2D* texture16 = new Texture2D();
	texture16->Load2D("Source/Laboratoare/Tema3/Textures/redstone.png", GL_REPEAT);
	Textures["redstone"] = texture16;
	Texture2D* texture17 = new Texture2D();
	texture17->Load2D("Source/Laboratoare/Tema3/Textures/ghast.png", GL_REPEAT);
	Textures["ghast"] = texture17;
	Texture2D* texture18 = new Texture2D();
	texture18->Load2D("Source/Laboratoare/Tema3/Textures/background.png", GL_REPEAT);
	Textures["background"] = texture18;

	player.Init();

	for (int j = 0; j < platforms_nr; j++)
	{
		int k = rand() % 3;
		for (int i = 0; i < platforms_columns; i++)
		{
			platform = new Platform();
			platform->Init();
			platforms[j][i] = *platform;
			if (i == 0)
				platforms[j][i].x = -2.5 - ((rand() % 5) * 0.3);
			if (i == 2)
				platforms[j][i].x = 2.5 + ((rand() % 5) * 0.3);
			platforms[j][i].y = -0.2 + (rand() % 2) * 0.7;
			platforms[j][i].scale = 6 + (rand() % 10) * 1.5;
			if (i == 1 && j == 0)
			{
				platforms[j][i].y = -0.2;
				platforms[j][i].scale = 30;
			}
			if (j == 0)
				platforms[j][i].z = 0;
			else
				platforms[j][i].z = platforms[j - 1][i].z - (platforms[j - 1][i].scale / 2)
				- (platforms[j][i].scale / 2) - 4 - ((rand() % 5) * 0.5);
			if (j % 2 && i == k)
			{
				int color_rand = 1 + rand() % 6;
				platforms[j][i].color = colors[color_rand];
			}
		}
	}

	for (int i = 0; i < skulls_nr; i++)
	{
		skull = new Skull();
		skull->Init();
		skulls[i] = *skull;
		int y = rand() % 2;
		if (y == 1)
			skulls[i].x = -9;
		else
			skulls[i].x = 9;
		skulls[i].z = -25 - i * 25;
		skulls[i].y = 0.5 + 0.5 * (rand() % 9);
		skulls[i].scale = 2 + rand() % 3;
	}
	for (int i = 0; i < flames_nr; i++)
	{
		flame = new Flame();
		flame->Init();
		flames[i] = *flame;
		int id = rand() % 3;
		flames[i].x = platforms[1 + i * 2][id].x - 0.65;
		flames[i].y = platforms[1 + i * 2][id].y + 0.03;
		float plat_dim = platforms[1 + i * 2][id].scale / 2 - 1;
		int sign = rand() % 3 - 1;
		flames[i].z = platforms[1 + i * 2][id].z + sign * (plat_dim / (1 + rand() % 4));
	}
	for (int i = 0; i < collects_nr; i++)
	{
		collect = new Collect();
		collect->Init();
		collects[i] = *collect;
		int id = rand() % 3;
		collects[i].x = platforms[i * 2][id].x;
		collects[i].y = platforms[i * 2][id].y + 0.5;
		float plat_dim = platforms[i * 2][id].scale / 2 - 1;
		int sign = rand() % 3 - 1;
		collects[i].z = platforms[i * 2][id].z + sign * (plat_dim / (1 + rand() % 4));
		collects[i].type = rand() % 3;
	}
	// main camera that follows the ball
	camera = new Tema3Camera::Camera();
	camera->Set(glm::vec3(player.x, 1.6 + player.y, 3), glm::vec3(player.x, player.y, -5), glm::vec3(0, 1, 0));

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	// 2nd camera that shows the HUD, mainly the fuel bar
	auto HUD = GetSceneCamera();
	HUD->SetOrthographic(0, window->GetResolution().x, 0, window->GetResolution().y, 0, 1);
	HUD->SetPosition(glm::vec3(0));
	HUD->SetRotation(glm::vec3(0));
	GetCameraInput()->SetActive(false);

	fuel.Init();
	boss.Init();

	platforms_speed = 0.025;
	lastPlatform = NULL;
	lastPlatformColor = "platformBlue";
	orangeEffect = false;
	orangeEffectCountdown = 0;
	speedBeforeOrangeEffect = 0.025;
	scoreCountdown = 5;
	shaderVariety = 0;
	player_type = "Player1";
	life_nr = life_max;
	ball_damaged = false;
	flame = NULL;
}

void Tema3::FrameStart()
{
	glClearColor(0.05, 0.05, 0.05, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::Update(float deltaTimeSeconds)
{
	shaderVariety -= deltaTimeSeconds;
	player.Update(deltaTimeSeconds);
	player.rotateSpeed = platforms_speed;
	if(player.thirdPerson)
		RenderSimpleMesh(meshes["player"], shaders[player_type], player.modelMatrix, Textures["player"]);
	// if player fall, -1 life
	if (player.y < -5)
	{
		cout << "You fall!" << endl;
		life_nr--;
		player.y = 5;
		player.x = 0;
		player.z = -0.25;
		player.scale = 0.4;
	}
	// check if orange platform effect
	if (orangeEffectCountdown <= 0 && orangeEffect)
	{
		player_type = "Player1";
		platforms_speed = speedBeforeOrangeEffect;
		orangeEffect = false;
	}
	else
		orangeEffectCountdown -= deltaTimeSeconds;
	// every 5 seconds it shows the score
	if (scoreCountdown <= 0)
	{
		cout << "Score: " << player.score << endl;
		scoreCountdown = 5;
	}
	else
		scoreCountdown -= deltaTimeSeconds;
	for (int j = 0; j < platforms_nr; j++)
	{
		int k = rand() % 3;
		for (int i = 0; i < platforms_columns; i++)
		{
			platforms[j][i].Update(deltaTimeSeconds);
			if(platforms[j][i].z + (platforms[j][i].scale / 2) > -60)
				RenderSimpleMesh(meshes[platforms[j][i].color], shaders["Texture"], platforms[j][i].modelMatrix, Textures[platforms[j][i].color]);
			// check collision
			if (CheckCollision(player.x, player.y, player.z, 0.3, platforms[j][i].x, platforms[j][i].y, platforms[j][i].z, platforms[j][i].width, platforms[j][i].height, platforms[j][i].scale))
			{
				if (player.y - (0.3 / 2) >= platforms[j][i].y) // if collision with platform and can stand on it
				{
					// if platforms is special platform apply vertex effect
					if(platforms[j][i].color == colors[2] || platforms[j][i].color == colors[3] || 
						platforms[j][i].color == colors[5] || platforms[j][i].color == colors[6])
						player_type = "Player2";
					// apply effects
					if (lastPlatform != &platforms[j][i])
					{
						if(!orangeEffect)
							shaderVariety = 6;
						if (platforms[j][i].color == colors[1]) // red platform
						{
							cout << "You hit the red platform!" << endl << "GAME OVER!" << endl;
							cout << "Final score: " << player.score << endl;
							exit(1);
						}
						if (platforms[j][i].color == colors[2]) // green platform
						{
							player.fuel += 20;
							if (player.fuel > 100)
								player.fuel = 100;
						}
						if (platforms[j][i].color == colors[3]) // yellow platform
							player.fuel -= 10;
						if (platforms[j][i].color == colors[4]) // orange platform
						{
							orangeEffect = true;
							orangeEffectCountdown = 5;
							speedBeforeOrangeEffect = platforms_speed;
							platforms_speed = 0.15;
							player_type = "Player2";
						}
						if (platforms[j][i].color == colors[5]) // black platform
						{
							life_nr--;
							cout << "You've lost a life" << endl;
						}
						if (platforms[j][i].color == colors[6] && life_nr < life_max) // white platform
						{
							life_nr++;
							cout << "You've won a life" << endl;
						}
					}
					// save the platform and its color and then change it to violet
					lastPlatform = &platforms[j][i];
					if(lastPlatform->color != colors[7])
						lastPlatformColor = platforms[j][i].color;
					platforms[j][i].color = colors[7];
					player.onPlatform = true;
					if(player.scale < 0.7)
						player.scale += 0.016;
				}
				else // if collision with platform but cannot stand on it
				{
					player.z += platforms[j][i].speed;
					player.jumpEffect = false;
				}
			}
			// if player is not on the platform anymore, restore it the color
			else if (lastPlatform == &platforms[j][i])
			{
				if(!orangeEffect)
					player_type = "Player1";
				player.onPlatform = false;
				platforms[j][i].color = lastPlatformColor;
			}
			// if platforms are out of screen, they respawn
			if (platforms[j][i].z > 40)
			{
				// random color
				if (j % 2)
				{
					if (i == k)
					{
						int color_rand = 1 + rand() % 6;
						// if fuel is nearly empty, give player a chance
						if (player.fuel < 30)
							color_rand = 2;
						platforms[j][i].color = colors[color_rand];
					}
					else
						platforms[j][i].color = colors[0];
				}
				if (i == 0)
					platforms[j][i].x = -2.5 - ((rand() % 5) * 0.3);
				if (i == 2)
					platforms[j][i].x = 2.5 + ((rand() % 5) * 0.3);
				platforms[j][i].y = -0.2 + (rand() % 2) * 0.7;
				platforms[j][i].scale = 6 + (rand() % 10) * 1.5;
				if (j == 0)
					platforms[j][i].z = platforms[platforms_nr - 1][i].z - (platforms[platforms_nr - 1][i].scale / 2)
					- (platforms[j][i].scale / 2) - 4 - ((rand() % 5) * 0.5);
				else
					platforms[j][i].z = platforms[j - 1][i].z - (platforms[j - 1][i].scale / 2)
					- (platforms[j][i].scale / 2) - 4 - ((rand() % 5) * 0.5);
			}
			platforms[j][i].speed = platforms_speed;
		}
	}
	// switch camera between 1st person or 3rd person
	if (!player.thirdPerson)
	{
		camera->Set(glm::vec3(player.x, player.y + 0.1, player.z), glm::vec3(player.x, player.y + 0.1, -5), glm::vec3(0, 1, 0));
		glm::mat4 modelMatrix = Transform3D::Translate(player.x + 0.5, player.y - 0.05, player.z - 0.75);
		modelMatrix *= Transform3D::RotateOX(0.25);
		modelMatrix *= Transform3D::RotateOZ(-0.25);
		modelMatrix *= Transform3D::Scale(0.04, 0.4, 0.04);
		RenderSimpleMesh(meshes["pickaxe_handler"], shaders["VertexColor"], modelMatrix);
		modelMatrix = Transform3D::Translate(player.x + 0.5, player.y + 0.15, player.z - 0.67);
		modelMatrix *= Transform3D::RotateOX(0.25);
		modelMatrix *= Transform3D::RotateOZ(-0.25);
		modelMatrix *= Transform3D::Scale(0.05, 0.05, 0.3);
		RenderSimpleMesh(meshes["pickaxe"], shaders["VertexColor"], modelMatrix);
		modelMatrix = Transform3D::Translate(player.x + 0.5, player.y + 0.16, player.z - 0.87);
		modelMatrix *= Transform3D::RotateOX(-0.4);
		modelMatrix *= Transform3D::RotateOZ(-0.25);
		modelMatrix *= Transform3D::Scale(0.05, 0.05, 0.15);
		RenderSimpleMesh(meshes["pickaxe"], shaders["VertexColor"], modelMatrix);
		modelMatrix = Transform3D::Translate(player.x + 0.61, player.y + 0.06, player.z - 0.6);
		modelMatrix *= Transform3D::RotateOX(1);
		modelMatrix *= Transform3D::RotateOZ(-0.25);
		modelMatrix *= Transform3D::Scale(0.05, 0.05, 0.15);
		RenderSimpleMesh(meshes["pickaxe"], shaders["VertexColor"], modelMatrix);
	}
	else
		camera->Set(glm::vec3(player.x, 1.6 + player.y, 3), glm::vec3(player.x, player.y, -5), glm::vec3(0, 1, 0));

	fuel.Update(deltaTimeSeconds);
	fuel.scaleX = player.fuel * 2;
	RenderMesh2D(meshes["fuel_bar"], shaders["VertexColor"], fuel.modelMatrix2);
	RenderMesh2D(meshes["fuel_backgr"], shaders["VertexColor"],fuel.modelMatrix1);

	boss.Update(deltaTimeSeconds);
	if (boss.boss_x >= player.x)
		boss.reverse = true;
	else
		boss.reverse = false;
	RenderSimpleMesh(meshes["boss"], shaders["Texture"], boss.modelMatrix1, Textures["ghast"]);
	if (!boss.ball_despawn)
		RenderSimpleMesh(meshes["boss_ball"], shaders["Boss_ball"], boss.modelMatrix4, Textures["boss_ball"]);
	// check collision with boss_ball
	if (CheckCollision(player.x, player.y, player.z, 0.3, boss.boss_x, boss.ball_y, boss.ball_z, 0.7, 0.7, 0.7))
	{
		if (!ball_damaged)
			life_nr--;
		ball_damaged = true;
	}
	else
		ball_damaged = false;

	if (life_nr <= 0)
	{
		cout << "You ran out of lives!" << endl << "GAME OVER!" << endl;
		cout << "Final score: " << player.score << endl;
		exit(1);
	}
	for (int i = 0; i < life_nr; i++)
	{
		glm::mat3 modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(550 + i * 80, 650);
		modelMatrix *= Transform2D::Scale(40, 40);
		RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
	}
	for (int i = 0; i < skulls_nr; i++)
	{
		skulls[i].Update(deltaTimeSeconds);
		if (skulls[i].z > 3)
		{
			skulls[i].y = 0.5 + 0.5 * (rand() % 9);
			if(i != 0)
				skulls[i].z = -25 + skulls[i - 1].z;
			else
				skulls[i].z = -25 + skulls[skulls_nr - 1].z;
			int y = rand() % 2;
			if (y == 1)
				skulls[i].x = -9;
			else
				skulls[i].x = 9;
			skulls[i].scale = 2 + rand() % 3;
		}
		if (skulls[i].z > -75)
		{
			RenderSimpleMesh(meshes["skull"], shaders["Texture"], skulls[i].modelMatrix1, Textures["skull"]);
			RenderSimpleMesh(meshes["boss_eye"], shaders["VertexColor"], skulls[i].modelMatrix2);
			RenderSimpleMesh(meshes["boss_eye"], shaders["VertexColor"], skulls[i].modelMatrix3);
			RenderSimpleMesh(meshes["skull_teeth"], shaders["VertexColor"], skulls[i].modelMatrix4);
			RenderSimpleMesh(meshes["skull_teeth"], shaders["VertexColor"], skulls[i].modelMatrix5);
			RenderSimpleMesh(meshes["skull_teeth"], shaders["VertexColor"], skulls[i].modelMatrix6);
		}
		if (skulls[i].z > -90)
		{
			RenderSimpleMesh(meshes["platformWhite"], shaders["Texture"], skulls[i].modelMatrix7, Textures["torch"]);
			RenderSimpleMesh(meshes["platformWhite"], shaders["Texture"], skulls[i].modelMatrix8, Textures["torch"]);
		}
	}
	for (int i = 0; i < flames_nr; i++)
	{
		flames[i].Update(deltaTimeSeconds);
		flames[i].z += platforms_speed;
		if(flames[i].z > -60)
			RenderSimpleMesh(meshes["flame"], shaders["Flame"], flames[i].modelMatrix, Textures["flame"]);
		if (flames[i].z > 5)
		{
				int id1 = rand() % 3;
				float farest = platforms[0][id1].z;
				int id2 = 0;
				for (int j = 1; j < platforms_nr; j++)
				{
					if (platforms[j][id1].z < farest)
					{
						id2 = j;
						farest = platforms[j][id1].z;
					}
				}
				flames[i].x = platforms[id2][id1].x - 0.65;
				flames[i].y = platforms[id2][id1].y + 0.03;
				float plat_dim = platforms[id2][id1].scale / 2 - 1;
				int sign = rand() % 3 - 1;
				flames[i].z = platforms[id2][id1].z + sign * (plat_dim / (1 + rand() % 4));
				if(&flames[i] == flame)
					flame = NULL;
		}
		if (CheckCollision(player.x, player.y, player.z, 0.3, flames[i].x + 0.75, flames[i].y, flames[i].z, 1.5, 1, 0.1) && &flames[i] != flame)
		{
			life_nr--;
			cout << "You've lost a life" << endl;
			flame = &flames[i];
		}
	}
	
	for (int i = 0; i < collects_nr; i++)
	{
		collects[i].Update(deltaTimeSeconds);
		collects[i].z += platforms_speed;
		if (!collects[i].collected && collects[i].z > -60)
		{
			if(collects[i].type == 0)
				RenderSimpleMesh(meshes["collect"], shaders["Texture"], collects[i].modelMatrix, Textures["diamond"]);
			else if(collects[i].type == 1)
				RenderSimpleMesh(meshes["collect"], shaders["Texture"], collects[i].modelMatrix, Textures["emerald"]);
			else
				RenderSimpleMesh(meshes["collect"], shaders["Texture"], collects[i].modelMatrix, Textures["redstone"]);
		}
		if (collects[i].z > 5)
		{
			collects[i].type = rand() % 3;
			int id1 = rand() % 3;
			float farest = platforms[0][id1].z;
			int id2 = 0;
			for (int j = 1; j < platforms_nr; j++)
			{
				if (platforms[j][id1].z < farest)
				{
					id2 = j;
					farest = platforms[j][id1].z;
				}
			}
			collects[i].x = platforms[id2][id1].x;
			collects[i].y = platforms[id2][id1].y + 0.5;
			collects[i].collected = false;
			collects[i].rotate = 0;
			collects[i].goUp = 0;
			collects[i].goUpBool = true;
			float plat_dim = platforms[id2][id1].scale / 2 - 1;
			int sign = rand() % 3 - 1;
			collects[i].z = platforms[id2][id1].z + sign * (plat_dim / (1 + rand() % 4));
			if (&collects[i] == collect)
				collect = NULL;
		}
		if (CheckCollision(player.x, player.y, player.z, 0.3, collects[i].x, collects[i].y, collects[i].z, 1, 1, 1) && &collects[i] != collect && !collects[i].collected)
		{
			collects[i].collected = true;
			if (collects[i].type == 0)
			{
				player.score += 2;
				cout << "You've collected a diamond" << endl;
			}
			if (collects[i].type == 1)
			{
				player.score++;
				cout << "You've collected a emerald" << endl;
			}
			if (collects[i].type == 2)
			{
				player.score--;
				cout << "You've collected a redstone" << endl;
			}
			collect = &collects[i];
		}
	}
	glm::mat4 modelMatrix = Transform3D::Translate(0, 0, -75);
	modelMatrix *= Transform3D::Scale(200, 200, 0.2);
	RenderSimpleMesh(meshes["background"], shaders["Texture"], modelMatrix, Textures["background"]);
}

void Tema3::FrameEnd()
{
}

void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;
	shader->Use();

	int loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix)); 

	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glUniform1f(glGetUniformLocation(shader->program, "variety"), shaderVariety);

	if (texture1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema3::OnInputUpdate(float deltaTime, int mods)
{
	float handlingSpeed = 6.5;
	if (window->KeyHold(GLFW_KEY_A) && player.x > -5)
		player.x -= deltaTime * handlingSpeed;
	if (window->KeyHold(GLFW_KEY_D) && player.x < 5)
		player.x += deltaTime * handlingSpeed;
	if (window->KeyHold(GLFW_KEY_W) && platforms_speed < 0.1 && !orangeEffect)
		platforms_speed += 0.00025;
	if (window->KeyHold(GLFW_KEY_S) && platforms_speed > 0.025 && !orangeEffect)
		platforms_speed -= 0.00025;
}

void Tema3::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_C)
		player.thirdPerson = !player.thirdPerson;
	if (key == GLFW_KEY_SPACE && player.canJump)
	{
		player.jumpEffect = true;
		player.cooldownJump = 0.5;
		player.onPlatform = false;
	}
}
bool Tema3::CheckCollision(float x1, float y1, float z1, float scale1, float x2, float y2, float z2, float scaleX2, float scaleY2, float scaleZ2)
{
	float x1_minX = x1 - (scale1 / 2);
	float x1_maxX = x1 + (scale1 / 2);
	float x1_minY = y1 - (scale1 / 2);
	float x1_maxY = y1 + (scale1 / 2);
	float x1_minZ = z1 - (scale1 / 2);
	float x1_maxZ = z1 + (scale1 / 2);

	float x2_minX = x2 - (scaleX2 / 2);
	float x2_maxX = x2 + (scaleX2 / 2);
	float x2_minY = y2 - (scaleY2 / 2);
	float x2_maxY = y2 + (scaleY2 / 2);
	float x2_minZ = z2 - (scaleZ2 / 2);
	float x2_maxZ = z2 + (scaleZ2 / 2);

	if ((x1_minX <= x2_maxX && x1_maxX >= x2_minX) &&
		(x1_minY <= x2_maxY && x1_maxY >= x2_minY) &&
		(x1_minZ <= x2_maxZ && x1_maxZ >= x2_minZ))
		return true;
	return false;
}
