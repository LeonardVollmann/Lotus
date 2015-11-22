#version 330 core

in DATA
{
	vec2 texCoord;
} fs_in;

out vec4 color;

void main()
{
	color = vec4(1, 1, 1, 1);
}