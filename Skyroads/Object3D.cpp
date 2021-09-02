#include "Object3D.h"

#include <Core/Engine.h>
using namespace std;

Mesh* Object3D::CreatePlatformBox(string name, glm::vec3 color, bool fill)
{
	Mesh* platformBox = new Mesh(name);

	vector<unsigned short> indices =
	{
		0, 1, 2,		1, 3, 2,
		2, 3, 7,		2, 7, 6,
		1, 7, 3,		1, 5, 7,
		6, 7, 4,		7, 5, 4,
		0, 4, 1,		1, 4, 5,
		2, 6, 4,		0, 2, 4,
	};
	if (!fill)
	{
		platformBox->SetDrawMode(GL_LINE_STRIP);
	}
	std::vector<glm::vec3> vertices
	{
		glm::vec3(-0.5, -0.5,  0.5),
		glm::vec3(0.5, -0.5,  0.5),
		glm::vec3(-0.5,  0.5,  0.5),
		glm::vec3(0.5,  0.5,  0.5),
		glm::vec3(-0.5, -0.5, -0.5),
		glm::vec3(0.5, -0.5, -0.5),
		glm::vec3(-0.5,  0.5, -0.5),
		glm::vec3(0.5,  0.5, -0.5)
	};

	std::vector<glm::vec2> textureCoords
	{
		glm::vec2(0, 1),
		glm::vec2(1, 1),
		glm::vec2(0, 1),
		glm::vec2(1, 1),
		glm::vec2(0, 0),
		glm::vec2(1, 0),
		glm::vec2(0, 0),
		glm::vec2(1, 0),

	};

	std::vector<glm::vec3> normals
	{
		glm::vec3(1, 1, 1)
	};

	platformBox->InitFromData(vertices, normals, textureCoords, indices);
	return platformBox;
}

Mesh* Object3D::CreateBoss(string name, glm::vec3 color, bool fill)
{
	Mesh* platformBox = new Mesh(name);

	vector<unsigned short> indices =
	{
		0, 1, 2,		1, 3, 2,
		2, 3, 7,		2, 7, 6,
		1, 7, 3,		1, 5, 7,
		6, 7, 4,		7, 5, 4,
		0, 4, 1,		1, 4, 5,
		2, 6, 4,		0, 2, 4,
	};
	if (!fill)
	{
		platformBox->SetDrawMode(GL_LINE_STRIP);
	}

	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, -0.5,  0.5), color),
		VertexFormat(glm::vec3(0, -0.5,  0.5), color),
		VertexFormat(glm::vec3(-0.5,  0.5,  0.5), color),
		VertexFormat(glm::vec3(0.5,  0.5,  0.5), color),
		VertexFormat(glm::vec3(0, -0.5, -0.5), color),
		VertexFormat(glm::vec3(0, -0.5, -0.5), color),
		VertexFormat(glm::vec3(-0.5,  0.5, -0.5), color),
		VertexFormat(glm::vec3(0.5,  0.5, -0.5), color),
	};

	platformBox->InitFromData(vertices, indices);
	return platformBox;
}

Mesh* Object3D::CreateBar(string name, glm::vec3 color, bool fill)
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
			VertexFormat(glm::vec3(0, 0, 0), color),
			VertexFormat(glm::vec3(1, 0, 0), color),
			VertexFormat(glm::vec3(1, 1, 0), color),
			VertexFormat(glm::vec3(0, 1, 0), color),
	};
	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object3D::CreateHeart(string name, glm::vec3 color)
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

Mesh* Object3D::CreateSkull(string name, glm::vec3 color)
{
	Mesh* skull = new Mesh(name);

	vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 0 };
	skull->SetDrawMode(GL_POLYGON);

	std::vector<glm::vec3> vertices
	{
		glm::vec3(0, 0,  0),

		glm::vec3(-0.75, 0,  0),
		glm::vec3(-0.75, 1,  0),
		glm::vec3(-0.85, 1.1,  0),
		glm::vec3(-0.95, 1.25,  0),
		glm::vec3(-1, 1.5,  0),
		glm::vec3(-0.95, 1.75,  0),
		glm::vec3(-0.85, 2,  0),
		glm::vec3(-0.75, 2.1,  0),

		glm::vec3(0, 2.2,  0),

		glm::vec3(0.75, 2.1,  0),
		glm::vec3(0.85, 2,  0),
		glm::vec3(0.95, 1.75,  0),
		glm::vec3(1, 1.5,  0),
		glm::vec3(0.95, 1.25,  0),
		glm::vec3(0.85, 1.1,  0),
		glm::vec3(0.75, 1,  0),
		glm::vec3(0.75, 0,  0)
	};

	std::vector<glm::vec2> textureCoords
	{
		glm::vec2(0.33, 0.33),

		glm::vec2(0.08, 0.33),
		glm::vec2(0.08, 0.66),
		glm::vec2(0.05, 0.69),
		glm::vec2(0.01, 0.74),
		glm::vec2(0, 0.82),
		glm::vec2(0.01, 0.9),
		glm::vec2(0.05, 0.98),
		glm::vec2(0.08, 1),

		glm::vec2(0.33, 1),

		glm::vec2(0.58, 1),
		glm::vec2(0.61, 0.98),
		glm::vec2(0.64, 0.9),
		glm::vec2(0.65, 0.82),
		glm::vec2(0.64, 0.74),
		glm::vec2(0.61, 0.69),
		glm::vec2(0.58, 0.66),
		glm::vec2(0.58, 0.33)
	};

	std::vector<glm::vec3> normals
	{
		glm::vec3(1, 1, 1)
	};

	skull->InitFromData(vertices, normals, textureCoords, indices);
	return skull;
}

Mesh* Object3D::CreateFlame(string name, glm::vec3 color)
{
	Mesh* skull = new Mesh(name);

	vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0 };
	skull->SetDrawMode(GL_POLYGON);

	std::vector<glm::vec3> vertices
	{
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0.15, 0.76, 0),
		glm::vec3(0.24, 0.94, 0),
		glm::vec3(0.39, 0.65, 0),
		glm::vec3(0.5, 1, 0),
		glm::vec3(0.65, 0.6, 0),
		glm::vec3(0.75, 0.9, 0),
		glm::vec3(0.83, 0.81, 0),
		glm::vec3(0.9, 1, 0),
		glm::vec3(1, 0.8, 0),
		glm::vec3(1, 0, 0)
	};

	std::vector<glm::vec2> textureCoords
	{
		glm::vec2(0, 0),
		glm::vec2(0, 1),
		glm::vec2(0.15, 0.76),
		glm::vec2(0.24, 0.94),
		glm::vec2(0.39, 0.65),
		glm::vec2(0.5, 1),
		glm::vec2(0.65, 0.6),
		glm::vec2(0.75, 0.9),
		glm::vec2(0.83, 0.81),
		glm::vec2(0.9, 1),
		glm::vec2(1, 0.8),
		glm::vec2(1, 0)
	};

	std::vector<glm::vec3> normals
	{
		glm::vec3(1, 1, 1)
	};

	skull->InitFromData(vertices, normals, textureCoords, indices);
	return skull;
}

Mesh* Object3D::CreatePickaxe(string name, glm::vec3 color, bool fill)
{
	Mesh* platformBox = new Mesh(name);

	vector<unsigned short> indices =
	{
		0, 1, 2,		1, 3, 2,
		2, 3, 7,		2, 7, 6,
		1, 7, 3,		1, 5, 7,
		6, 7, 4,		7, 5, 4,
		0, 4, 1,		1, 4, 5,
		2, 6, 4,		0, 2, 4,
	};
	if (!fill)
	{
		platformBox->SetDrawMode(GL_LINE_STRIP);
	}

	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-0.5, -0.5,  0.5), color),
		VertexFormat(glm::vec3(0.5, -0.5,  0.5), color),
		VertexFormat(glm::vec3(-0.5,  0.5,  0.5), color),
		VertexFormat(glm::vec3(0.5,  0.5,  0.5), color),
		VertexFormat(glm::vec3(-0.5, -0.5, -0.5), color),
		VertexFormat(glm::vec3(0.5, -0.5, -0.5), color),
		VertexFormat(glm::vec3(-0.5,  0.5, -0.5), color),
		VertexFormat(glm::vec3(0.5,  0.5, -0.5), color),
	};

	platformBox->InitFromData(vertices, indices);
	return platformBox;
}