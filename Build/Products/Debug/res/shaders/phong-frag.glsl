#version 330 core

const int MAX_POINT_LIGHTS = 4;
const int MAX_SPOT_LIGHTS = 4;

in vec2 texCoord;
in vec3 normal;
in vec3 worldPos;

out vec4 fragColor;

uniform vec3 cameraPos;
uniform sampler2D diffuse;
uniform vec4 baseColor;
uniform float specularIntensity;
uniform float specularPower;

#include lighting.glsl

uniform vec3 ambientLight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

void main()
{
	vec4 totalLight = vec4(ambientLight, 1.0);
	vec4 textureColor = texture(diffuse, texCoord);
	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);

	if (textureColor != vec4(0.0, 0.0, 0.0, 0.0))
	{
		color = textureColor;
	}
	else
	{
		color = baseColor;
	}

	totalLight += calcDirectionalLight(directionalLight, normal);

	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		if (pointLights[i].base.intensity > 0) totalLight += calcPointLight(pointLights[i], normal);
	}

	for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		if (spotLights[i].pointLight.base.intensity > 0) totalLight += calcSpotLight(spotLights[i], normal);
	}


	fragColor = color * totalLight;
}