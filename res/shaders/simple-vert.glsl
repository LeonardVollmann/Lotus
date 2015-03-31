#version 330 core

layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec4 vertex_color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix;
uniform mat4 ml_matrix;
uniform vec3 u_color;

out vec4 color;

void main()
{
	color = vec4(u_color, 1.0f);
	// gl_Position = pr_matrix * ml_matrix * vec4(vertex_pos, 1.0f);
	// gl_Position = pr_matrix vw_matrix * ml_matrix * vec4(vertex_pos, 1.0f);
	gl_Position = pr_matrix * vw_matrix * ml_matrix * vec4(vertex_pos, 1.0f);
}