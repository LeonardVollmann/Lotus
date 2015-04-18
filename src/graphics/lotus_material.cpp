#include "lotus_material.hpp"

const Material *Material::CURRENT;

Material::Material(const vec4 &color, const Texture &texture, float specularIntensity, float specularPower) :
	m_color(color),
	m_texture(texture),
	m_specularIntensity(specularIntensity),
	m_specularPower(specularPower) {}

void Material::bind() const
{
	CURRENT = this;
	m_texture.bind(0);
}