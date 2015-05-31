#version 330 core

in DATA
{
	vec2 texCoord;
} fs_in;

out vec4 fragColor;

uniform sampler2D diffuse;

uniform vec4 baseColor;
uniform vec3 ambientLight;

void main()
{
	fragColor = (texture(diffuse, fs_in.texCoord) + baseColor) * vec4(ambientLight, 1.0);
}