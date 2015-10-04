#version 330 core

layout (location = 0) in vec3 vertex_pos;
layout (location = 1) in vec2 vertex_texCoord;

uniform mat4 vp_matrix;

out DATA
{
	vec2 texCoord;
} vs_out;

void main()
{
	vs_out.texCoord = vertex_texCoord;
	gl_Position = vp_matrix * vec4(vertex_pos, 1.0);
}