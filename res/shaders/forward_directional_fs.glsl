#include forward_fs.glsl
#include lighting.glsl

uniform DirectionalLight light_directional;

vec4 calcLightingEffect(vec3 normal, vec3 worldPos, vec3 cameraPos)
{
	return calcDirectionalLight(light_directional, normal, worldPos, cameraPos);
}

#include forward_main_fs.glsl