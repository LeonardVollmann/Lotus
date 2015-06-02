#include forward_shared-frag.glsl

uniform SpotLight spotLight;

vec4 calcLightingEffect(vec3 normal, vec3 worldPos, vec3 cameraPos)
{
	return calcSpotLight(spotLight, normal, worldPos, cameraPos);
}

#include forward_main-frag.glsl