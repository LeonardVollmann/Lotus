#version 330 core

in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D diffuse;
uniform vec4 baseColor;
uniform vec3 ambientLight;

void main()
{
	fragColor = (texture(diffuse, texCoord) + baseColor) * vec4(ambientLight, 1.0);
}