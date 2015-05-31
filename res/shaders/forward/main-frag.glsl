void main()
{
	vec3 normal = fs_in.tbn_matrix * (255.0/128.0 * texture(normalMap, fs_in.texCoord).xyz - 1);
	fragColor = (texture(diffuse, fs_in.texCoord) + baseColor) * calcLightingEffect(normal, fs_in.worldPos, cameraPos);
}