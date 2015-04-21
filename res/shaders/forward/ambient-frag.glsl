#version 330 core

in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D diffuse;
uniform vec4 baseColor;
uniform vec3 ambientLight;

void main()
{
	vec4 textureColor = texture(diffuse, texCoord);
	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
	
	if (textureColor != vec4(0.0, 0.0, 0.0, 0.0))
	{
		color = textureColor;
	}
	else
	{
		color = baseColor;
	}
	
	fragColor = color * vec4(ambientLight, 1.0);
}