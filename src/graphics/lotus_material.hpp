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
	mutable std::map<std::string, vec3>		m_vec3Map;
	mutable std::map<std::string, vec4>		m_vec4Map;
	mutable std::map<std::string, float>	m_floatMap;
	mutable std::map<std::string, Texture*>	m_textureMap;
public:
	virtual ~Material();
	
	void bind() const;
	void bindTexture(const std::string &name, unsigned int unit) const;
	
	const vec3 &getVec3(const std::string &name) const;
	const vec4 &getVec4(const std::string &name) const;
	float getFloat(const std::string &name) const;
	Texture *getTexture(const std::string &name) const;
	
	inline void addVec3(const std::string &name, const vec3 &value)	const { m_vec3Map.insert(std::pair<std::string, vec3>(name, value)); }
	inline void addVec4(const std::string &name, const vec4 &value)	const { m_vec4Map.insert(std::pair<std::string, vec4>(name, value)); }
	inline void addFloat(const std::string &name, float value)		const { m_floatMap.insert(std::pair<std::string, float>(name, value)); }
	inline void addTexture(const std::string &name, Texture *value)	const { m_textureMap.insert(std::pair<std::string, Texture*>(name, value)); }
	
	inline void setVec3(const std::string &name, const vec3 &value) const { if (m_vec4Map.find(name) != m_vec4Map.end()) m_vec3Map.at(name) = value; }
	inline void setVec4(const std::string &name, const vec4 &value) const { if (m_vec3Map.find(name) != m_vec3Map.end()) m_vec4Map.at(name) = value; }
	inline void setFloat(const std::string name, float value)		const { if (m_floatMap.find(name) != m_floatMap.end()) m_floatMap.at(name) = value; }
	inline void setTexture(const std::string &name, Texture *value) const { if (m_textureMap.find(name) != m_textureMap.end()) m_textureMap.at(name) = value; }
};

#endif