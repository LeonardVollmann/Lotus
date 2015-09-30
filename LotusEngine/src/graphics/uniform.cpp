#include "uniform.hpp"
#include "shader.hpp"

namespace lotus { namespace graphics {

	template <typename VAR_T>
	VarUniform<VAR_T>::VarUniform(const ShaderResource *shader, const char *name, unsigned char **owner, size_t varOffset) :
		m_location(glGetUniformLocation(shader->getShaderProgram(), name)),
		m_owner(owner),
		m_varOffset(varOffset) {}

	template <typename VAR_T>
	void VarUniform<VAR_T>::update(const Shader *shader) const
	{
		shader->setUniform(m_location, *(VAR_T*) (*m_owner + m_varOffset));
	}

	template class VarUniform<int>;
	template class VarUniform<float>;
	template class VarUniform<maths::Vector2f>;
	template class VarUniform<maths::Vector3f>;
	template class VarUniform<maths::Vector4f>;
	template class VarUniform<maths::Matrix4f>;

	template <typename VAR_T>
	MaterialUniform<VAR_T>::MaterialUniform(const ShaderResource *shader, const char *uniformName, const std::string &varName) :
		m_location(glGetUniformLocation(shader->getShaderProgram(), uniformName)),
		m_name(varName) {}

	template <typename VAR_T>
	void MaterialUniform<VAR_T>::update(const Shader *shader) const
	{
		shader->setUniform(m_location, *(VAR_T*) Material::CURRENT->get(m_name));
	}

	template class MaterialUniform<int>;
	template class MaterialUniform<float>;
	template class MaterialUniform<maths::Vector2f>;
	template class MaterialUniform<maths::Vector3f>;
	template class MaterialUniform<maths::Vector4f>;
	template class MaterialUniform<maths::Matrix4f>;

	SamplerUniform::SamplerUniform(const ShaderResource *shader, const char *name, int samplerSlot) :
		m_location(glGetUniformLocation(shader->getShaderProgram(), name)),
		m_samplerSlot(samplerSlot) {}

	void SamplerUniform::update(const Shader *shader) const
	{
		shader->setUniform(m_location, m_samplerSlot);
	}

	template <typename VAR_T>
	FunctionUniform<VAR_T>::FunctionUniform(const ShaderResource *shader, const char *name, VAR_T (*getUniformValue)()) :
		m_location(glGetUniformLocation(shader->getShaderProgram(), name)),
		m_getUniformValue(getUniformValue) {}

	template <typename VAR_T>
	void FunctionUniform<VAR_T>::FunctionUniform::update(const Shader *shader) const
	{
		shader->setUniform(m_location, m_getUniformValue());
	}

	template class FunctionUniform<int>;
	template class FunctionUniform<float>;
	template class FunctionUniform<maths::Vector2f>;
	template class FunctionUniform<maths::Vector3f>;
	template class FunctionUniform<maths::Vector4f>;
	template class FunctionUniform<maths::Matrix4f>;

	template <typename VAR_T, unsigned int NUM_MEMBERS, void GET_LOCATIONS(const ShaderResource *shader, const std::string &name, GLuint *locations)>
	StructUniform<VAR_T, NUM_MEMBERS, GET_LOCATIONS>::StructUniform(const ShaderResource *shader, const std::string &name)
	{
		GET_LOCATIONS(shader, name, m_locations);
	}

	template <typename VAR_T, unsigned int NUM_MEMBERS, void GET_LOCATIONS(const ShaderResource *shader, const std::string &name, GLuint *locations)>
	void StructUniform<VAR_T, NUM_MEMBERS, GET_LOCATIONS>::update(const Shader *shader) const
	{
		VAR_T::setUniformValues(shader, (GLuint*) m_locations);
	}

	template class StructUniform<AmbientLight, 1, AmbientLight::getUniformLocations>;
	template class StructUniform<DirectionalLight, 3, DirectionalLight::getUniformLocations>;
	template class StructUniform<PointLight, 7, PointLight::getUniformLocations>;
	template class StructUniform<SpotLight, 9, SpotLight::getUniformLocations>;

} }
