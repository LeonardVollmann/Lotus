#include "lotus_material.hpp"

const Material *Material::CURRENT;

void Material::bind() const
{
	CURRENT = this;
}

void Material::bindTexture(const std::string &name, unsigned int unit) const
{
	getTexture(name).bind(unit);
}

const vec3 &Material::getVec3(const std::string &name) const
{
	auto it = m_vec3Map.find(name);
	if (it == m_vec3Map.end()) return vec3::ZERO;
	else return it->second;
}

const vec4 &Material::getVec4(const std::string &name) const
{
	auto it = m_vec4Map.find(name);
	if (it == m_vec4Map.end()) return vec4::ZERO;
	else return it->second;
}

float Material::getFloat(const std::string &name) const
{
	auto it = m_floatMap.find(name);
	if (it == m_floatMap.end()) return 0.0f;
	else return it->second;
}

const Texture &Material::getTexture(const std::string &name) const
{
	auto it = m_textureMap.find(name);
	if (it == m_textureMap.end()) return Texture("default.png");
	else return it->second;
}