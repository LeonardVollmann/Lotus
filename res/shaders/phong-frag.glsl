#version 330 core

const int MAX_POINT_LIGHTS = 4;

struct BaseLight
{
	vec3 color;
	float intensity;
};

struct DirectionalLight
{
	BaseLight base;
	vec3 direction;
};

struct Attenuation
{
	float constant;
	float linear;
	float exponent;
};

struct PointLight
{
	BaseLight base;
	Attenuation atten;
	vec3 pos;
};

in vec2 texCoord;
in vec3 normal;
in vec3 worldPos;

out vec4 fragColor;

uniform vec3 cameraPos;
uniform sampler2D diffuse;
uniform vec4 baseColor;
uniform float specularIntensity;
uniform float specularPower;

uniform vec3 ambientLight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

vec4 calcLight(BaseLight base, vec3 direction, vec3 normal)
{
	float diffuseFactor = dot(normal, -direction);
	vec4 diffuseColor = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 specularColor = vec4(0.0, 0.0, 0.0, 0.0);

	if (diffuseFactor > 0)
	{
		diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor;

		vec3 directionToCamera = normalize(cameraPos - worldPos);
		vec3 reflectDirection = normalize(reflect(direction, normal));

		float specularFactor = pow(dot(directionToCamera, reflectDirection), specularPower);

		if (specularFactor > 0)
		{
			specularColor = vec4(base.color, 1.0) * specularIntensity * specularFactor * base.intensity;
		}
	}

	return diffuseColor + specularColor;
}

vec4 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal)
{
	return calcLight(directionalLight.base, -directionalLight.direction, normal);
}

vec4 calcPointLight(PointLight pointLight, vec3 normal)
{
	vec3 lightDirection = worldPos - pointLight.pos;
	float distance = length(lightDirection);
	lightDirection = normalize(lightDirection);

	vec4 color = calcLight(pointLight.base, lightDirection, normal);

	float attenuation = pointLight.atten.constant +
						pointLight.atten.linear * distance +
						pointLight.atten.exponent * distance * distance +
						0.000001;

	return color / attenuation;
}

void main()
{
	vec4 totalLight = vec4(ambientLight, 1.0);
	vec4 textureColor = texture(diffuse, texCoord);
	vec4 color = baseColor;

	if (textureColor != vec4(0.0, 0.0, 0.0, 0.0))
	{
		color += textureColor;
	}

	totalLight += calcDirectionalLight(directionalLight, normal);

	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		totalLight += calcPointLight(pointLights[i], normal);
	}

	fragColor = color * totalLight;
}