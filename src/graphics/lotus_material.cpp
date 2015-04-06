#include "lotus_material.hpp"

namespace lotus { namespace graphics { 

	Material::Material(const maths::vec4 &color, const Texture &texture, float specularIntensity, float specularPower) :
		m_color(color),
		m_texture(texture),
		m_specularIntensity(specularIntensity),
		m_specularPower(specularPower) {}

	void Material::bind() const
	{
		m_texture.bind(0);
	}

	void Material::unbind() const
	{
		m_texture.unbind();
	}

} }