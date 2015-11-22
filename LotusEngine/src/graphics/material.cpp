#include "material.hpp"

#include <typeinfo>

namespace lotus
{
namespace graphics
{

const Material *Material::CURRENT;

Material::Material(Texture *diffuse,
                   maths::vec4f color,
                   float specularIntensity,
                   float specularPower,
                   Texture *normalMap,
                   Texture *dispMap,
                   float dispMapScale,
                   float dispMapOffset)
{
	set("diffuse", diffuse);
	set("color", new maths::vec4f(color));
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
	// TODO: Find a better way to do this
	for (auto it = m_values.begin(); it != m_values.end(); it++)
	{
		const std::type_info &type = typeid(it->second);
		if (type == typeid(float *))
			delete (float *)it->second;
		else if (type == typeid(maths::vec2f *))
			delete (maths::vec2f *)it->second;
		else if (type == typeid(maths::vec3f *))
			delete (maths::vec3f *)it->second;
		else if (type == typeid(maths::vec4f *))
			delete (maths::vec4f *)it->second;
		else if (type == typeid(Texture *))
			delete (Texture *)it->second;
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
	m_values.insert(std::pair<std::string, void *>(name, value));
}

} // namespace graphics
} // namespace lotus