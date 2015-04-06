#version 330 core

layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec2 vertex_texCoord;
layout(location = 2) in vec3 vertex_normal;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix;
uniform mat4 ml_matrix;

out vec2 texCoord;
out vec3 normal;
out vec3 worldPos;

void main()
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * vec4(vertex_pos, 1.0);
	texCoord = vertex_texCoord;
	normal = (ml_matrix * vec4(vertex_normal, 0.0)).xyz;
	worldPos = (ml_matrix * vec4(vertex_pos, 1.0)).xyz;
}