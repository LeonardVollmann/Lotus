#include forward/shared-frag.glsl

uniform PointLight pointLight;

vec4 calcLightingEffect(vec3 normal, vec3 worldPos, vec3 cameraPos)
{
	return calcPointLight(pointLight, normal, worldPos, cameraPos);
}

#include forward/main-frag.glsl