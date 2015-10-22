#include forward3d_fs.glsl
#include lighting.glsl

uniform SpotLight light_spot;

vec4 calcLightingEffect(vec3 normal, vec3 worldPos, vec3 cameraPos)
{
	return calcSpotLight(light_spot, normal, worldPos, cameraPos);
}

#include forward3d_main_fs.glsl