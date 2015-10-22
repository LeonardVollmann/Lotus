#include forward3d_fs.glsl
#include lighting.glsl

uniform PointLight light_point;

vec4 calcLightingEffect(vec3 normal, vec3 worldPos, vec3 cameraPos)
{
	return calcPointLight(light_point, normal, worldPos, cameraPos);
}

#include forward3d_main_fs.glsl