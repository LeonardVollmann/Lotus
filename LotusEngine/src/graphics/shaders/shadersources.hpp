#ifndef LOTUS_SHADER_SOURCES_HPP_INCLUDED
#define LOTUS_SHADER_SOURCES_HPP_INCLUDED

namespace lotus { namespace graphics {

#define SOURCE_LIGHTING																										\
	"struct BaseLight\n"																									\
	"{\n"																													\
	"	vec3 color;\n"																										\
	"	float intensity;\n"																									\
	"};\n"																													\
	"\n"																													\
	"struct DirectionalLight\n"																								\
	"{\n"																													\
	"	BaseLight base;\n"																									\
	"	vec3 direction;\n"																									\
	"};\n"																													\
	"\n"																													\
	"struct Attenuation\n"																									\
	"{\n"																													\
	"	float constant;\n"																									\
	"	float linear;\n"																									\
	"	float exponent;\n"																									\
	"};\n"																													\
	"\n"																													\
	"struct PointLight\n"																									\
	"{\n"																													\
	"	BaseLight base;\n"																									\
	"	Attenuation atten;\n"																								\
	"	vec3 pos;\n"																										\
	"	float range;\n"																										\
	"};\n"																													\
	"\n"																													\
	"struct SpotLight\n"																									\
	"{\n"																													\
	"	PointLight pointLight;\n"																							\
	"	vec3 direction;\n"																									\
	"	float cutoff;\n"																									\
	"};\n"																													\
	"\n"																													\
	"vec4 calcLight(BaseLight base, vec3 direction, vec3 normal, vec3 worldPos, vec3 cameraPos)\n"							\
	"{\n"																													\
	"	float diffuseFactor = dot(normal, -direction);\n"																	\
	"	vec4 diffuseColor = vec4(0.0, 0.0, 0.0, 0.0);\n"																	\
	"	vec4 specularColor = vec4(0.0, 0.0, 0.0, 0.0);\n"																	\
	"	\n"																													\
	"	if (diffuseFactor > 0)\n"																							\
	"	{\n"																												\
	"		diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor;\n"										\
	"		\n"																												\
	"		vec3 directionToCamera = normalize(cameraPos - worldPos);\n"													\
	"		vec3 reflectDirection = normalize(reflect(direction, normal));\n"												\
	"		\n"																												\
	"		float specularFactor = pow(dot(directionToCamera, reflectDirection), material_specularPower);\n"				\
	"		\n"																												\
	"		if (specularFactor > 0)\n"																						\
	"		{\n"																											\
	"			specularColor = vec4(base.color, 1.0) * material_specularIntensity * specularFactor * base.intensity;\n"	\
	"		}\n"																											\
	"	}\n"																												\
	"	\n"																													\
	"	return diffuseColor + specularColor;\n"																				\
	"}\n"																													\
	"\n"																													\
	"vec4 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 worldPos, vec3 cameraPos)\n"			\
	"{\n"																													\
	"	return calcLight(directionalLight.base, -directionalLight.direction, normal, worldPos, cameraPos);\n"				\
	"}\n"																													\
	"\n"																													\
	"vec4 calcPointLight(PointLight pointLight, vec3 normal, vec3 worldPos, vec3 cameraPos)\n"								\
	"{\n"																													\
	"	vec3 lightDirection = worldPos - pointLight.pos;\n"																	\
	"	float distance = length(lightDirection);\n"																			\
	"	\n"																													\
	"	if (distance > pointLight.range) return vec4(0.0, 0.0, 0.0, 0.0);\n"												\
	"	\n"																													\
	"	lightDirection = normalize(lightDirection);\n"																		\
	"	\n"																													\
	"	vec4 color = calcLight(pointLight.base, lightDirection, normal, worldPos, cameraPos);\n"							\
	"	\n"																													\
	"	float attenuation = pointLight.atten.constant +\n"																	\
	"		pointLight.atten.linear * distance +\n"																			\
	"		pointLight.atten.exponent * distance * distance +\n"															\
	"		0.000001;\n"																									\
	"	\n"																													\
	"	return color / attenuation;\n"																						\
	"}\n"																													\
	"\n"																													\
	"vec4 calcSpotLight(SpotLight spotLight, vec3 normal, vec3 worldPos, vec3 cameraPos)\n"									\
	"{\n"																													\
	"	vec3 lightDirection = normalize(worldPos - spotLight.pointLight.pos);\n"											\
	"	float spotFactor = dot(lightDirection, spotLight.direction);\n"														\
	"	\n"																													\
	"	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);\n"																			\
	"	\n"																													\
	"	if (spotFactor > spotLight.cutoff)\n"																				\
	"	{\n"																												\
	"		color = calcPointLight(spotLight.pointLight, normal, worldPos, cameraPos) *\n"									\
	"		(1.0 - (1.0 - spotFactor) / (1.0 - spotLight.cutoff));\n"														\
	"	}\n"																												\
	"	\n"																													\
	"	return color;\n"																									\
	"}\n"

#define SOURCE_BASIC_VERT										\
	"#version 330 core\n"										\
	"\n"														\
	"layout(location = 0) in vec3 vertex_pos;\n"				\
	"layout(location = 1) in vec2 vertex_texCoord;\n"			\
	"\n"														\
	"out vec2 texCoord;\n"										\
	"\n"														\
	"uniform mat4 mvp_matrix;\n"								\
	"\n"														\
	"void main()\n"												\
	"{\n"														\
	"	texCoord = vertex_texCoord;\n"							\
	"	gl_Position = mvp_matrix * vec4(vertex_pos, 1.0);\n"	\
	"}\n"

#define SOURCE_BASIC_FRAG															\
	"#version 330 core\n"															\
	"\n"																			\
	"in vec2 texCoord;\n"															\
	"\n"																			\
	"out vec4 fragColor;\n"															\
	"\n"																			\
	"uniform vec4 material_color;\n"												\
	"uniform sampler2D material_diffuse;\n"											\
	"\n"																			\
	"void main()\n"																	\
	"{\n"																			\
	"	fragColor = texture(material_diffuse, texCoord) + material_color;\n"		\
	"}\n"

#define SOURCE_FORWARD_SAMPLING																											\
	"vec2 calcParallaxTexCoords(sampler2D dispMap, mat3 tbn_matrix, vec3 directionToCamera, vec2 texCoord, float scale, float bias)\n"	\
	"{\n"																																\
	"	return texCoord + (directionToCamera * tbn_matrix).xy * (texture(dispMap, texCoord).x * scale + bias);\n"						\
	"}\n"

#define SOURCE_FORWARD_VERT																		\
	"#version 330 core\n"																		\
	"\n"																						\
	"layout(location = 0) in vec3 vertex_pos;\n"												\
	"layout(location = 1) in vec2 vertex_texCoord;\n"											\
	"layout(location = 2) in vec3 vertex_normal;\n"												\
	"layout(location = 3) in vec3 vertex_tangent;\n"											\
	"\n"																						\
	"uniform mat4 mvp_matrix;\n"																\
	"uniform mat4 transform_modelMatrix;\n"														\
	"\n"																						\
	"out DATA\n"																				\
	"{\n"																						\
	"	vec2 texCoord;\n"																		\
	"	vec3 worldPos;\n"																		\
	"	mat3 tbn_matrix;\n"																		\
	"} vs_out;\n"																				\
	"\n"																						\
	"void main()\n"																				\
	"{\n"																						\
	"	gl_Position = mvp_matrix * vec4(vertex_pos, 1.0);\n"									\
	"	vs_out.texCoord = vertex_texCoord;\n"													\
	"	vs_out.worldPos = (transform_modelMatrix * vec4(vertex_pos, 1.0)).xyz;\n"				\
	"\n"																						\
	"	vec3 normal = normalize((transform_modelMatrix * vec4(vertex_normal, 0.0)).xyz);\n"		\
	"	vec3 tangent = normalize((transform_modelMatrix * vec4(vertex_tangent, 0.0)).xyz);\n"	\
	"\n"																						\
	"	tangent = normalize(tangent - dot(tangent, normal) * normal);\n"						\
	"\n"																						\
	"	vec3 biTangent = normalize(cross(tangent, normal));\n"									\
	"\n"																						\
	"	vs_out.tbn_matrix = mat3(tangent, biTangent, normal);\n"								\
	"}\n"

#define SOURCE_FORWARD_FRAG							\
	"#version 330 core\n"							\
	"\n"											\
	"in DATA\n"										\
	"{\n"											\
	"	vec2 texCoord;\n"							\
	"	vec3 worldPos;\n"							\
	"	mat3 tbn_matrix;\n"							\
	"} fs_in;\n"									\
	"\n"											\
	"out vec4 fragColor;\n"							\
	"\n"											\
	"uniform vec4 material_color;\n"				\
	"uniform float material_specularIntensity;\n"	\
	"uniform float material_specularPower;\n"		\
	"uniform float material_dispMapScale;\n"		\
	"uniform float material_dispMapBias;\n"			\
	"uniform vec3 camera_pos;\n"					\
	"\n"											\
	"uniform sampler2D material_diffuse;\n"			\
	"uniform sampler2D material_normalMap;\n"		\
	"uniform sampler2D material_dispMap;\n"

#define SOURCE_FORWARD_MAIN_FRAG																											\
	"void main()\n"																															\
	"{\n"																																	\
	"	vec2 texCoord = calcParallaxTexCoords(material_dispMap, fs_in.tbn_matrix, normalize(camera_pos - fs_in.worldPos),\n"				\
	"										fs_in.texCoord, material_dispMapScale, material_dispMapBias);\n"								\
	"\n"																																	\
	"	vec3 normal = fs_in.tbn_matrix * (255.0/128.0 * texture(material_normalMap, texCoord).xyz - 1);\n"									\
	"	fragColor = (texture(material_diffuse, texCoord) + material_color) * calcLightingEffect(normal, fs_in.worldPos, camera_pos);\n"		\
	"}\n"

#define SOURCE_FORWARD_AMBIENT_FRAG																													\
	"uniform vec3 light_ambient;\n"																													\
	"\n"																																			\
	"void main()\n"																																	\
	"{\n"																																			\
	"	fragColor = (texture(material_diffuse, calcParallaxTexCoords(material_dispMap, fs_in.tbn_matrix, normalize(camera_pos - fs_in.worldPos),\n"	\
	"																fs_in.texCoord, material_dispMapScale,\n"										\
	"																material_dispMapBias)) + material_color) * vec4(light_ambient, 1.0);\n"			\
	"}\n"

#define SOURCE_FORWARD_DIRECTIONAL_FRAG													\
	"uniform DirectionalLight light_directional;\n"										\
	"\n"																				\
	"vec4 calcLightingEffect(vec3 normal, vec3 worldPos, vec3 cameraPos)\n"				\
	"{\n"																				\
	"	return calcDirectionalLight(light_directional, normal, worldPos, cameraPos);\n"	\
	"}\n"																				\

#define SOURCE_FORWARD_POINT_FRAG											\
	"uniform PointLight light_point;\n"										\
	"\n"																	\
	"vec4 calcLightingEffect(vec3 normal, vec3 worldPos, vec3 cameraPos)\n"	\
	"{\n"																	\
	"	return calcPointLight(light_point, normal, worldPos, cameraPos);\n"	\
	"}\n"

#define SOURCE_FORWARD_SPOT_FRAG											\
	"uniform SpotLight light_spot;\n"										\
	"\n"																	\
	"vec4 calcLightingEffect(vec3 normal, vec3 worldPos, vec3 cameraPos)\n"	\
	"{\n"																	\
	"	return calcSpotLight(light_spot, normal, worldPos, cameraPos);\n"	\
	"}\n"

#define SOURCE_BATCH2D_VERT										\
	"#version 330 core\n"										\
	"\n"														\
	"layout(location = 0) in vec3 vertex_pos;\n"				\
	"layout(location = 1) in vec2 vertex_texCoord;\n"			\
	"\n"														\
	"uniform mat4 vp_matrix;\n"									\
	"\n"														\
	"out vec2 texCoord;\n"										\
	"\n"														\
	"void main()\n"												\
	"{\n"														\
	"	texCoord = vertex_texCoord;\n"							\
	"	gl_Position = vp_matrix * vec4(vertex_pos, 1.0);\n"		\
	"}\n"

#define SOURCE_BATCH2D_FRAG							\
	"#version 330 core\n"							\
	"\n"											\
	"in vec2 texCoord;\n"							\
	"\n"											\
	"out vec4 fragColor;\n"							\
	"\n"											\
	"void main()\n"									\
	"{\n"											\
	"	fragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"		\
	"}\n"

} }

#endif
