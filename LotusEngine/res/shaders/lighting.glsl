struct BaseLight
{
	Vector3f color;
	float intensity;
};

struct DirectionalLight
{
	BaseLight base;
	Vector3f direction;
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
	Vector3f pos;
	float range;
};

struct SpotLight
{
	PointLight pointLight;
	Vector3f direction;
	float cutoff;
};

vec4 calcLight(BaseLight base, Vector3f direction, Vector3f normal, Vector3f worldPos, Vector3f cameraPos)
{
	float diffuseFactor = dot(normal, -direction);
	vec4 diffuseColor = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 specularColor = vec4(0.0, 0.0, 0.0, 0.0);

	if (diffuseFactor > 0)
	{
		diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor;

		Vector3f directionToCamera = normalize(cameraPos - worldPos);
		Vector3f reflectDirection = normalize(reflect(direction, normal));

		float specularFactor = pow(dot(directionToCamera, reflectDirection), material_specularPower);

		if (specularFactor > 0)
		{
			specularColor = vec4(base.color, 1.0) * material_specularIntensity * specularFactor * base.intensity;
		}
	}

	return diffuseColor + specularColor;
}

vec4 calcDirectionalLight(DirectionalLight directionalLight, Vector3f normal, Vector3f worldPos, Vector3f cameraPos)
{
	return calcLight(directionalLight.base, -directionalLight.direction, normal, worldPos, cameraPos);
}

vec4 calcPointLight(PointLight pointLight, Vector3f normal, Vector3f worldPos, Vector3f cameraPos)
{
	Vector3f lightDirection = worldPos - pointLight.pos;
	float distance = length(lightDirection);

	if (distance > pointLight.range) return vec4(0.0, 0.0, 0.0, 0.0);

	lightDirection = normalize(lightDirection);

	vec4 color = calcLight(pointLight.base, lightDirection, normal, worldPos, cameraPos);

	float attenuation = pointLight.atten.constant +
		pointLight.atten.linear * distance +
		pointLight.atten.exponent * distance * distance +
		0.000001;

	return color / attenuation;
}

vec4 calcSpotLight(SpotLight spotLight, Vector3f normal, Vector3f worldPos, Vector3f cameraPos)
{
	Vector3f lightDirection = normalize(worldPos - spotLight.pointLight.pos);
	float spotFactor = dot(lightDirection, spotLight.direction);

	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);

	if (spotFactor > spotLight.cutoff)
	{
		color = calcPointLight(spotLight.pointLight, normal, worldPos, cameraPos) *
		(1.0 - (1.0 - spotFactor) / (1.0 - spotLight.cutoff));
	}

	return color;
}