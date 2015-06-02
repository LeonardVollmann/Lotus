#include forward_sampling.glsl

void main()
{
	vec2 texCoord = calcParallaxTexCoords(dispMap, fs_in.tbn_matrix, normalize(cameraPos - fs_in.worldPos), fs_in.texCoord, dispMapScale, dispMapBias);

	vec3 normal = fs_in.tbn_matrix * (255.0/128.0 * texture(normalMap, texCoord).xyz - 1);
	fragColor = (texture(diffuse, texCoord) + baseColor) * calcLightingEffect(normal, fs_in.worldPos, cameraPos);
}