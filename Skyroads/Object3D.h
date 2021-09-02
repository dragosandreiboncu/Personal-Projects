#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
using namespace std;

namespace Object3D
{
	Mesh* CreatePlatformBox(string name, glm::vec3 color, bool fill = false);
	Mesh* CreateBoss(string name, glm::vec3 color, bool fill = false);
	Mesh* CreateBar(string name, glm::vec3 color, bool fill = false);
	Mesh* CreateHeart(string name, glm::vec3 color);
	Mesh* CreateSkull(string name, glm::vec3 color);
	Mesh* CreateFlame(string name, glm::vec3 color);
	Mesh* CreatePickaxe(string name, glm::vec3 color, bool fill = false);
}

