#version 330 core

in vec2 texCoord;

out vec4 frag_color;

uniform vec4 baseColor;
uniform sampler2D diffuse;

void main()
{
	vec4 textureColor = texture(diffuse, texCoord);
	
	if (textureColor != vec4(0.0, 0.0, 0.0, 0.0))
	{
		frag_color = textureColor;
	}
	else
	{
		frag_color = baseColor;
	}
}