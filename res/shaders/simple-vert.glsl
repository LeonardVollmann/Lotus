#version 330 core

layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec4 vertex_color;

out vec4 color;

void main()
{
	color = vertex_color;
	gl_Position = vec4(vertex_pos, 1.0f);
}