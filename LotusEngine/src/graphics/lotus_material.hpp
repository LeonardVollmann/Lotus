#ifndef LOTUS_MATERIAL_HPP_INCLUDED
#define LOTUS_MATERIAL_HPP_INCLUDED

#include "lotus_texture.hpp"
#include "lotus_vec2.hpp"
#include "lotus_vec3.hpp"
#include "lotus_vec4.hpp"

#include <map>
#include <string>

class Material
{
public:
	static const Material *CURRENT;
private:
	mutable std::map<std::string, void*> m_values;
public:
	Material() {}
	Material(Texture *diffuse, vec4 color = vec4::ZERO, float specularIntensity = 2.0f, float specularPower = 8.0f,
			 Texture *normalMap = new Texture("default_normal.png"), Texture *dispMap = new Texture("default_disp.png"),
			 float dispMapScale = 0.0f, float dispMapOffset = 0.0f);
	virtual ~Material();
	
	void bind() const;
	void bindTexture(const std::string &name, unsigned int unit) const;
	
	void set(const std::string &name, void *value) const;
	
	inline const void *get(const std::string &name)				 const { return (const void*) m_values[name]; }
	inline const float *getFloat(const std::string &name)		const { return (const float*) get(name); }
	inline const vec2 *getVec2(const std::string &name)			const { return (const vec2*) get(name); }
	inline const vec3 *getVec3(const std::string &name)			const { return (const vec3*) get(name); }
	inline const vec4 *getVec4(const std::string &name)			const { return (const vec4*) get(name); }
	inline const Texture *getTexture(const std::string &name)	const { return (const Texture*) get(name); }
};

#endif