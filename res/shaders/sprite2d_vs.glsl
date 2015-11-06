#version 330 core

layout (location = 0) in vec3 vertex_pos;
layout (location = 1) in vec2 vertex_texCoord;

uniform mat4 scene_projection;

out DATA
{
	vec2 texCoord;
} vs_out;

void main()
{
	vs_out.texCoord = vertex_texCoord;
	gl_Position = scene_projection * vec4(vertex_pos, 1.0);
}