#version 330 core

in DATA
{
	vec2 texCoord;
} fs_in;

out vec4 fragColor;

uniform vec4 baseColor;
uniform sampler2D diffuse;

void main()
{
	fragColor = texture(diffuse, fs_in.texCoord) + baseColor;
}