#include forward/shared-frag.glsl

uniform PointLight pointLight;

void main()
{
	fragColor = (texture(diffuse, texCoord) + baseColor) * calcPointLight(pointLight, normal);
}