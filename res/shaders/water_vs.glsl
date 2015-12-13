#version 330 core

layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec2 vertex_texCoord;
layout(location = 2) in vec3 vertex_normal;
layout(location = 3) in vec3 vertex_tangent;

uniform mat4 vp_matrix;

void main()
{
	gl_Position = vp_matrix * vec4(vertex_pos, 1.0);
}