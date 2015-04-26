#version 330 core

in vec2 texCoord;

out vec4 fragColor;

uniform vec4 baseColor;
uniform sampler2D diffuse;

void main()
{
	vec4 textureColor = texture(diffuse, texCoord);
	
	if (textureColor != vec4(0.0, 0.0, 0.0, 0.0))
	{
		fragColor = textureColor;
	}
	else
	{
		fragColor = baseColor;
	}
}