#version 330

in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texture;
in vec3 frag_color;

uniform sampler2D texture_1;

layout(location = 0) out vec4 out_color;

void main()
{
	vec4 color = texture2D(texture_1, frag_texture);         
	out_color = color;
}