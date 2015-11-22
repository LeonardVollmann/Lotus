vec2 calcParallaxTexCoords(sampler2D dispMap, mat3 tbn_matrix, vec3 directionToCamera, vec2 texCoord, float scale, float bias)
{
	return texCoord + (directionToCamera * tbn_matrix).xy * (texture(dispMap, texCoord).x * scale + bias);
}