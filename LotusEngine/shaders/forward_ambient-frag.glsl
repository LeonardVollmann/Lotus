#include forward_shared-frag.glsl

uniform vec3 ambientLight;

#include forward_sampling.glsl

void main()
{
	fragColor = (texture(diffuse, calcParallaxTexCoords(dispMap, fs_in.tbn_matrix, normalize(cameraPos - fs_in.worldPos), fs_in.texCoord, dispMapScale, dispMapBias)) + baseColor) 
		* vec4(ambientLight, 1.0);
}