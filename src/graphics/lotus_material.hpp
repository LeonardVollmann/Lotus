#ifndef LOTUS_MATERIAL_HPP_INCLUDED
#define LOTUS_MATERIAL_HPP_INCLUDED

#include "lotus_texture.hpp"
#include "../maths/lotus_vec3.hpp"
#include "../maths/lotus_vec4.hpp"

#include <string>
#include <map>

class Material
{
public:
	static const Material *CURRENT;
private:
	std::map<std::string, vec3>		m_vec3Map;
	std::map<std::string, vec4>		m_vec4Map;
	std::map<std::string, float>	m_floatMap;
	std::map<std::string, Texture>	m_textureMap;
public:
	void bind() const;
	void bindTexture(const std::string &name, unsigned int unit) const;
	
	const vec3 &getVec3(const std::string &name) const;
	const vec4 &getVec4(const std::string &name) const;
	float getFloat(const std::string &name) const;
	const Texture &getTexture(const std::string &name) const;
	
	inline void addVec3(const std::string &name, const vec3 &value)			{ m_vec3Map.insert(std::pair<std::string, vec3>(name, value)); }
	inline void addVec4(const std::string &name, const vec4 &value)			{ m_vec4Map.insert(std::pair<std::string, vec4>(name, value)); }
	inline void addFloat(const std::string &name, float value)				{ m_floatMap.insert(std::pair<std::string, float>(name, value)); }
	inline void addTexture(const std::string &name, const Texture &value)	{ m_textureMap.insert(std::pair<std::string, Texture>(name, value)); }
};

#endif