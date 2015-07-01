#include forward_shared-frag.glsl

uniform vec3 ambientLight;

#include forward_sampling.glsl

void main()
{
	fragColor = (texture(material_diffuse, calcParallaxTexCoords(material_dispMap, fs_in.tbn_matrix, normalize(camera_pos - fs_in.worldPos),
																 fs_in.texCoord, material_dispMapScale, material_dispMapBias)) + material_color) * vec4(ambientLight, 1.0);
}