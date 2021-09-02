#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
using namespace std;

namespace Object2D
{
	Mesh* CreateTriangle(string name, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateSquare(string name, glm::vec3 default, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateHalfCircle(string name, glm::vec3 color);
	Mesh* CreateCircle(string name, glm::vec3 color);
	Mesh* CreateHeart(string name, glm::vec3 color);
}

