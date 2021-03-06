#version 330 core

layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec2 vertex_texCoord;

out vec2 texCoord;

uniform mat4 mvp_matrix;

void main()
{
	texCoord = vertex_texCoord;
	gl_Position = mvp_matrix * vec4(vertex_pos, 1.0);
}