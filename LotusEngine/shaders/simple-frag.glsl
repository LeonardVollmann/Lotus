#version 330 core

in DATA
{
	vec2 texCoord;
} fs_in;

out vec4 fragColor;

uniform vec4 material_color;
uniform sampler2D material_diffuse;

void main()
{
	fragColor = texture(material_diffuse, fs_in.texCoord) + material_color;
}