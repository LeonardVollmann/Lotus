#include forward3d_sampling.glsl

void main()
{
	vec2 texCoord = calcParallaxTexCoords(material_dispMap, fs_in.tbn_matrix, normalize(camera_pos - fs_in.worldPos),
										fs_in.texCoord, material_dispMapScale, material_dispMapBias);

	vec3 normal = fs_in.tbn_matrix * (255.0/128.0 * texture(material_normalMap, texCoord).xyz - 1);
	fragColor = (texture(material_diffuse, texCoord) + material_color) * calcLightingEffect(normal, fs_in.worldPos, camera_pos);
}