#include forward/shared-frag.glsl

uniform SpotLight spotLight;

void main()
{
	fragColor = (texture(diffuse, texCoord) + baseColor) * calcSpotLight(spotLight, normal);
}