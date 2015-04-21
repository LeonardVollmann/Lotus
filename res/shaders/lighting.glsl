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
	float range;
};

struct SpotLight
{
	PointLight pointLight;
	vec3 direction;
	float cutoff;
};

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
	
	if (distance > pointLight.range) return vec4(0.0, 0.0, 0.0, 0.0);
	
	lightDirection = normalize(lightDirection);
	
	vec4 color = calcLight(pointLight.base, lightDirection, normal);
	
	float attenuation = pointLight.atten.constant +
	pointLight.atten.linear * distance +
	pointLight.atten.exponent * distance * distance +
	0.000001;
	
	return color / attenuation;
}

vec4 calcSpotLight(SpotLight spotLight, vec3 normal)
{
	vec3 lightDirection = normalize(worldPos - spotLight.pointLight.pos);
	float spotFactor = dot(lightDirection, spotLight.direction);
	
	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
	
	if (spotFactor > spotLight.cutoff)
	{
		color = calcPointLight(spotLight.pointLight, normal) *
		(1.0 - (1.0 - spotFactor) / (1.0 - spotLight.cutoff));
	}
	
	return color;
}