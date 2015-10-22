#version 330 core

in vec2 texCoord;

out vec4 fragColor;

uniform vec4 material_color;
uniform sampler2D material_diffuse;

void main()
{
	fragColor = texture(material_diffuse, texCoord) + material_color;
}