#version 330 core

layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec2 vertex_texCoord;
layout(location = 2) in vec3 vertex_normal;
layout(location = 3) in vec3 vertex_tangent;

uniform mat4 mvp_matrix;
uniform mat4 ml_matrix;

out DATA
{
	vec2 texCoord;
	vec3 worldPos;
	vec3 normal;
} vs_out;

void main()
{
	gl_Position = mvp_matrix * vec4(vertex_pos, 1.0);
	vs_out.texCoord = vertex_texCoord;
	vs_out.worldPos = (ml_matrix * vec4(vertex_pos, 1.0)).xyz;
	vs_out.normal = normalize((ml_matrix * vec4(vertex_normal, 0.0)).xyz);
}