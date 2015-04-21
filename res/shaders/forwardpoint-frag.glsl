#version 330 core

#include lighting.glsl

in vec2 texCoord;
in vec3 normal;
in vec3 worldPos;

out vec4 fragColor;

uniform vec3 cameraPos;

uniform sampler2D diffuse;
uniform vec4 baseColor;
uniform float specularIntensity;
uniform float specularPower;

uniform PointLight pointLight;

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

vec4 calcPointLight(PointLight pointLight, vec3 normal)
{
	vec3 lightDirection = worldPos - pointLight.pos;
	float distance = length(lightDirection);
	
	if (distance > pointLight.range) return vec4(0.0, 0.0, 0.0, 0.0);
	
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
	
	fragColor = color * calcPointLight(pointLight, normal);
}