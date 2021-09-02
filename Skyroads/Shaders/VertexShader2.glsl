#version 330

layout(location = 0) in vec3 v_position;
layout(location = 3) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 1) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float variety;

out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;

void main()
{

	frag_position = v_position;
	frag_normal = v_normal;
	frag_texture = v_texture;
	frag_color = vec3(0.9, 0.9 - 0.12 * (6.5-variety), 0.9 - 0.12 * (6.5-variety));

	frag_position.x = v_position.x + sin(v_position.x * 15 + variety * 15) / 2;
	frag_position.y = v_position.y + cos(v_position.y * 5 + variety * 5) / 10;
	frag_position.z = v_position.z + sin(v_position.z * 8 + variety * 8) / 20;

	gl_Position	= Projection * View * Model * vec4(frag_position, 1.0);
}
