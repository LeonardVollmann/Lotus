#include "lotus_material.hpp"

const Material *Material::CURRENT;

Material::Material(Texture *diffuse, vec4 color, float specularIntensity, float specularPower, Texture *normalMap, Texture *dispMap, float dispMapScale, float dispMapOffset)
{
	setTexture("diffuse", diffuse);
	setVec4("color", color);
	setFloat("specularIntensity", specularIntensity);
	setFloat("specularPower", specularPower);
	setTexture("normalMap", normalMap);
	setTexture("dispMap", dispMap);

	float baseBias = dispMapScale / 2.0f;
	setFloat("dispMapScale", dispMapScale);
	setFloat("dispMapBias", -baseBias + baseBias * dispMapOffset);
}

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
		setVec3(name, vec3::ZERO);
		return vec3::ZERO;
	}
	else return it->second;
}

const vec4 &Material::getVec4(const std::string &name) const
{
	auto it = m_vec4Map.find(name);
	if (it == m_vec4Map.end())
	{
		setVec4(name, vec4::ZERO);
		return vec4::ZERO;
	}
	else return it->second;
}

float Material::getFloat(const std::string &name) const
{
	auto it = m_floatMap.find(name);
	if (it == m_floatMap.end())
	{
		setFloat(name, 0.0f);
		return 0.0f;
	}
	else return it->second;
}

Texture *Material::getTexture(const std::string &name) const
{
	auto it = m_textureMap.find(name);
	if (it == m_textureMap.end())
	{
		if (name == "diffuse") setTexture(name, new Texture("default.png"));
		else if (name == "normalMap") setTexture(name, new Texture("default_normal.png"));
		else if (name == "dispMap") setTexture(name, new Texture("default_disp.png"));
		else setTexture(name, new Texture("white.png"));
		
		return getTexture(name);
	}
	else return it->second;
}

void Material::setVec3(const std::string &name, const vec3 &value) const
{
	auto it = m_vec3Map.find(name);
	if (it == m_vec3Map.end())
	{
		m_vec3Map.insert(std::pair<std::string, vec3>(name, value));
	}
	else
	{
		m_vec3Map.at(name) = value;
	}
}

void Material::setVec4(const std::string &name, const vec4 &value) const
{
	auto it = m_vec4Map.find(name);
	if (it == m_vec4Map.end())
	{
		m_vec4Map.insert(std::pair<std::string, vec4>(name, value));
	}
	else
	{
		m_vec4Map.at(name) = value;
	}
}

void Material::setFloat(const std::string name, float value) const
{
	auto it = m_floatMap.find(name);
	if (it == m_floatMap.end())
	{
		m_floatMap.insert(std::pair<std::string, float>(name, value));
	}
	else
	{
		m_floatMap.at(name) = value;
	}
}

void Material::setTexture(const std::string &name, Texture *value) const
{
	auto it = m_textureMap.find(name);
	if (it == m_textureMap.end())
	{
		m_textureMap.insert(std::pair<std::string, Texture*>(name, value));
	}
	else
	{
		delete m_textureMap.at(name);
		m_textureMap.at(name) = value;
	}
}