#ifndef LOTUS_MATERIAL_HPP_INCLUDED
#define LOTUS_MATERIAL_HPP_INCLUDED

#include "lotus_texture.hpp"
#include "lotus_vec3.hpp"
#include "lotus_vec4.hpp"

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
	Material() {}
	Material(Texture *diffuse, vec4 color = vec4::ZERO, float specularIntensity = 2.0f, float specularPower = 8.0f,
			 Texture *normalMap = new Texture("default_normal.png"), Texture *dispMap = new Texture("default_disp.png"),
			 float dispMapScale = 0.0f, float dispMapOffset = 0.0f);
	virtual ~Material();
	
	void bind() const;
	void bindTexture(const std::string &name, unsigned int unit) const;
	
	const vec3 &getVec3(const std::string &name) const;
	const vec4 &getVec4(const std::string &name) const;
	float getFloat(const std::string &name) const;
	Texture *getTexture(const std::string &name) const;
	
	void setVec3(const std::string &name, const vec3 &value) const;
	void setVec4(const std::string &name, const vec4 &value) const;
	void setFloat(const std::string name, float value) const;
	void setTexture(const std::string &name, Texture *value) const;
};

#endif