#ifndef LOTUS_MATERIAL_HPP_INCLUDED
#define LOTUS_MATERIAL_HPP_INCLUDED

#include "lotus_texture.hpp"
#include "../maths/lotus_vec4.hpp"

class Material
{
public:
	static const Material *CURRENT;
private:
	vec4 	m_color;
	Texture m_texture;

	float 	m_specularIntensity;
	float	m_specularPower;
public:
	Material(const vec4 &color, const Texture &texture, float specularIntensity, float specularPower);

	void bind() const;

	inline const vec4 &getColor() 				const { return m_color; }
	inline const Texture &getTexture() 			const { return m_texture; }
	inline const float getSpecularIntensity() 	const { return m_specularIntensity; }
	inline const float getSpecularPower()		const { return m_specularPower; }

	inline void setColor(const vec4 &color) 					{ m_color = color; }
	inline void setTexture(const Texture &texture) 				{ m_texture = texture; }
	inline void setSpecularIntensity(float specularIntensity) 	{ m_specularIntensity = specularIntensity; }
	inline void setSpecularPower(float specularPower)			{ m_specularPower = specularPower; }
};

#endif