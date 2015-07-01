#version 330 core

const int MAX_POINT_LIGHTS = 4;
const int MAX_SPOT_LIGHTS = 4;

in DATA
{
	vec2 texCoord;
	vec3 worldPos;
	vec3 normal;
} fs_in;

out vec4 fragColor;

uniform vec3 camera_pos;
uniform sampler2D material_diffuse;
uniform vec4 material_color;
uniform float material_specularIntensity;
uniform float material_specularPower;

#include lighting.glsl

uniform vec3 ambientLight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

void main()
{
	vec4 totalLight = vec4(ambientLight, 1.0);
	vec4 color = texture(diffuse, fs_in.texCoord) + baseColor;

	totalLight += calcDirectionalLight(directionalLight, fs_in.normal, fs_in.worldPos, cameraPos);

	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		if (pointLights[i].base.intensity > 0) totalLight += calcPointLight(pointLights[i], fs_in.normal, fs_in.worldPos, cameraPos);
	}

	for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		if (spotLights[i].pointLight.base.intensity > 0) totalLight += calcSpotLight(spotLights[i], fs_in.normal, fs_in.worldPos, cameraPos);
	}


	fragColor = color * totalLight;
}