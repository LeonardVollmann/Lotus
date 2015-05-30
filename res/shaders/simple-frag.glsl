#version 330 core

in vec2 texCoord;

out vec4 fragColor;

uniform vec4 baseColor;
uniform sampler2D diffuse;

void main()
{
	fragColor = texture(diffuse, texCoord) + baseColor;
}