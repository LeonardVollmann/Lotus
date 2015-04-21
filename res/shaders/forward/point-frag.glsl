#include forward/shared-frag.glsl

uniform PointLight pointLight;

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
	
	fragColor = color * calcPointLight(pointLight, normal);
}