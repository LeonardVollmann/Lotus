#include "lotus_material.hpp"

#include <typeinfo>

const Material *Material::CURRENT;

Material::Material(Texture *diffuse, vec4 color, float specularIntensity, float specularPower, Texture *normalMap, Texture *dispMap, float dispMapScale, float dispMapOffset)
{
	set("diffuse", diffuse);
	set("color", new vec4(color));
	set("specularIntensity", new float(specularIntensity));
	set("specularPower", new float(specularPower));
	set("normalMap", normalMap);
	set("dispMap", dispMap);

	float baseBias = dispMapScale / 2.0f;
	set("dispMapScale", new float(dispMapScale));
	set("dispMapBias", new float(-baseBias + baseBias * dispMapOffset));
}

Material::~Material()
{
	for (auto it = m_values.begin(); it != m_values.end(); it++)
	{
		const std::type_info &type = typeid(it->second);
		if (type == typeid(float*)) delete (float*) it->second;
		else if (type == typeid(vec2*)) delete (vec2*) it->second;
		else if (type == typeid(vec3*)) delete (vec3*) it->second;
		else if (type == typeid(vec4*)) delete (vec4*) it->second;
		else if (type == typeid(Texture*)) delete (Texture*) it->second;
	}
}

void Material::bind() const
{
	CURRENT = this;
}

void Material::bindTexture(const char *name, unsigned int unit) const
{
	getTexture(name)->bind(unit);
}

void Material::set(const char *name, void *value) const
{
	m_values.insert(std::pair<const char*, void*>(name, value));
}