#include forward_shared-frag.glsl

uniform DirectionalLight directionalLight;

vec4 calcLightingEffect(vec3 normal, vec3 worldPos, vec3 cameraPos)
{
	return calcDirectionalLight(directionalLight, normal, worldPos, cameraPos);
}

#include forward_main-frag.glsl