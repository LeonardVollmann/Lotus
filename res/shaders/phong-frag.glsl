#version 330 core

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

in vec2 texCoord;
in vec3 normal;

uniform sampler2D diffuse;
uniform vec4 baseColor;
uniform vec3 ambientLight;
uniform DirectionalLight directionalLight;

out vec4 color;

vec4 calcLight(BaseLight base, vec3 direction, vec3 normal)
{
	float diffuseFactor = dot(normal, -direction);
	vec4 diffuseColor = vec4(0.0, 0.0, 0.0, 0.0);
	if (diffuseFactor > 0)
	{
		diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor;
	}

	return diffuseColor;
}

vec4 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal)
{
	return calcLight(directionalLight.base, -directionalLight.direction, normal);
}

void main()
{
	vec4 textureColor = texture(diffuse, texCoord);

	vec4 totalLight = vec4(ambientLight, 1.0);
	totalLight += calcDirectionalLight(directionalLight, normal);

	color = textureColor * totalLight + baseColor * totalLight;
}