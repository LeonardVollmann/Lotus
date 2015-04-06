#version 330 core

in vec2 texCoord;

out vec4 frag_color;

uniform vec4 baseColor;
uniform sampler2D diffuse;

void main()
{
	frag_color = texture(diffuse, texCoord) + baseColor;
}