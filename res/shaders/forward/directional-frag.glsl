#include forward/shared-frag.glsl

uniform DirectionalLight directionalLight;

void main()
{
	fragColor = (texture(diffuse, texCoord) + baseColor) * calcDirectionalLight(directionalLight, normal);
}