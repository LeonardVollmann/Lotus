#include forward/shared-frag.glsl

uniform DirectionalLight directionalLight;

void main()
{
	fragColor = (texture(diffuse, fs_in.texCoord) + baseColor) * calcDirectionalLight(directionalLight, fs_in.normal, fs_in.worldPos, cameraPos);
}