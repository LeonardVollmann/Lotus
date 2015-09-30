#include "material.hpp"

#include <typeinfo>

namespace lotus { namespace graphics {

	const Material *Material::CURRENT;

	Material::Material(Texture *diffuse, maths::Vector4f color, float specularIntensity, float specularPower, Texture *normalMap, Texture *dispMap, float dispMapScale, float dispMapOffset)
	{
		set("diffuse", diffuse);
		set("color", new maths::Vector4f(color));
		set("specularIntensity", new float(specularIntensity));
		set("specularPower", new float(specularPower));
		set("normalMap", normalMap);
		set("dispMap", dispMap);

		float baseBias = dispMapScale / 2.0f;
		set("dispMapScale", new float(dispMapScale));
		set("dispMapBias", new float(-baseBias + baseBias * dispMapOffset));
	}

	Material::~Material()
	{
		for (auto it = m_values.begin(); it != m_values.end(); it++)
		{
			const std::type_info &type = typeid(it->second);
			if (type == typeid(float*)) delete (float*) it->second;
			else if (type == typeid(maths::Vector2f*)) delete (maths::Vector2f*) it->second;
			else if (type == typeid(maths::Vector3f*)) delete (maths::Vector3f*) it->second;
			else if (type == typeid(maths::Vector4f*)) delete (maths::Vector4f*) it->second;
			else if (type == typeid(Texture*)) delete (Texture*) it->second;
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

	void Material::set(const std::string &name, void *value) const
	{
		m_values.insert(std::pair<std::string, void*>(name, value));
	}

} }