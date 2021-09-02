#include "Object2D.h"

#include <Core/Engine.h>
using namespace std;

Mesh* Object2D::CreateTriangle(string name, float length, glm::vec3 color, bool fill)
{
	Mesh* triangle = new Mesh(name);

	vector<unsigned short> indices = { 0, 1, 2 };
	if (!fill)
	{
		triangle->SetDrawMode(GL_LINE_LOOP);
	}
	else
	{
		indices.push_back(0);
		indices.push_back(2);
	}
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(0, length, 0), color),
		VertexFormat(glm::vec3((length / 2) * sqrt(3), length / 2, 0), color),
	};
	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Object2D::CreateSquare(string name, glm::vec3 default, float length, glm::vec3 color, bool fill)
{
	Mesh* square = new Mesh(name);

	vector<unsigned short> indices = { 0, 1, 2, 3 };
	if (!fill) 
	{
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else 
	{
		indices.push_back(0);
		indices.push_back(2);
	}
	vector<VertexFormat> vertices
	{
			VertexFormat(default, color),
			VertexFormat(glm::vec3(length, 0, 0), color),
			VertexFormat(glm::vec3(length, length, 0), color),
			VertexFormat(glm::vec3(0, length, 0), color),
	};
	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateHalfCircle(string name, glm::vec3 color)
{
	Mesh* circle = new Mesh(name);

	float radius = 25;
	vector<unsigned short> indices;
	circle->SetDrawMode(GL_LINE_STRIP);
	for (int i = 0; i <= 180; i++)
	{
		indices.push_back(i);
	}
	vector<VertexFormat> vertices;
	for (int i = -90; i <= 90; i++)
	{
		float angle = i * M_PI / 180;
		vertices.push_back(VertexFormat(glm::vec3(cos(angle) * radius, sin(angle) * radius, 1), color));
	}
	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* Object2D::CreateCircle(string name, glm::vec3 color)
{
	Mesh* circle = new Mesh(name);

	float radius = 1;
	vector<unsigned short> indices;
	circle->SetDrawMode(GL_POLYGON);
	for (int i = 0; i <= 360; i++)
	{
		indices.push_back(i);
	}
	vector<VertexFormat> vertices;
	for (int i = 0; i <= 360; i++)
	{
		float angle = i * M_PI / 180;
		vertices.push_back(VertexFormat(glm::vec3(cos(angle) * radius, sin(angle) * radius, 1), color));
	}
	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* Object2D::CreateHeart(string name, glm::vec3 color)
{
	Mesh* heart = new Mesh(name);

	vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0 };
	heart->SetDrawMode(GL_POLYGON);

	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0.25, 0), color),

		VertexFormat(glm::vec3(0.5, 1, 0), color),
		VertexFormat(glm::vec3(0.5, 1.25, 0), color),
		VertexFormat(glm::vec3(0.38, 1.35, 0), color),

		VertexFormat(glm::vec3(0.25, 1.35, 0), color),
		VertexFormat(glm::vec3(0.2, 1.3, 0), color),

		VertexFormat(glm::vec3(0, 1.2, 0), color),

		VertexFormat(glm::vec3(-0.2, 1.3, 0), color),
		VertexFormat(glm::vec3(-0.25, 1.35, 0), color),
		VertexFormat(glm::vec3(-0.38, 1.35, 0), color),

		VertexFormat(glm::vec3(-0.5, 1.25, 0), color),
		VertexFormat(glm::vec3(-0.5, 1, 0), color),
	};
	heart->InitFromData(vertices, indices);
	return heart;
}