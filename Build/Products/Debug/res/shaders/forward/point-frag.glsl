#include forward/shared-frag.glsl

uniform PointLight pointLight;

void main()
{
	fragColor = (texture(diffuse, fs_in.texCoord) + baseColor) * calcPointLight(pointLight, fs_in.normal, fs_in.worldPos, cameraPos);
}