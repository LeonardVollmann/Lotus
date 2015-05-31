#include forward/shared-frag.glsl

uniform SpotLight spotLight;

void main()
{
	fragColor = (texture(diffuse, fs_in.texCoord) + baseColor) * calcSpotLight(spotLight, fs_in.normal, fs_in.worldPos, cameraPos);
}