#include "lotus_material.hpp"

const Material *Material::CURRENT;

Material::~Material()
{
	for (auto it = m_textureMap.begin(); it != m_textureMap.end(); it++)
	{
		delete it->second;
	}
}

void Material::bind() const
{
	CURRENT = this;
}

void Material::bindTexture(const std::string &name, unsigned int unit) const
{
	getTexture(name)->bind(unit);
}

const vec3 &Material::getVec3(const std::string &name) const
{
	auto it = m_vec3Map.find(name);
	if (it == m_vec3Map.end())
	{
		addVec3(name, vec3::ZERO);
		return vec3::ZERO;
	}
	else return it->second;
}

const vec4 &Material::getVec4(const std::string &name) const
{
	auto it = m_vec4Map.find(name);
	if (it == m_vec4Map.end())
	{
		addVec4(name, vec4::ZERO);
		return vec4::ZERO;
	}
	else return it->second;
}

float Material::getFloat(const std::string &name) const
{
	auto it = m_floatMap.find(name);
	if (it == m_floatMap.end())
	{
		addFloat(name, 0.0f);
		return 0.0f;
	}
	else return it->second;
}

Texture *Material::getTexture(const std::string &name) const
{
	auto it = m_textureMap.find(name);
	if (it == m_textureMap.end())
	{
		addTexture(name, new Texture("default.png"));
		return getTexture(name);
	}
	else return it->second;
}