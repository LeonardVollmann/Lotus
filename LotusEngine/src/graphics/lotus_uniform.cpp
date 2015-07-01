#include "lotus_uniform.hpp"
#include "lotus_shader.hpp"

template<typename VAR_T>
Uniform<VAR_T>::Uniform(const Shader *shader, const char *name, unsigned char **owner, size_t varOffset) :
	m_location(glGetUniformLocation(shader->getShaderProgram(), name)),
	m_owner(owner),
	m_varOffset(varOffset) {}

template<typename VAR_T>
void Uniform<VAR_T>::update(const Shader *shader) const
{
	shader->setUniform(m_location, *(VAR_T*) (*m_owner + m_varOffset));
}

template class Uniform<int>;
template class Uniform<float>;
template class Uniform<vec2>;
template class Uniform<vec3>;
template class Uniform<vec4>;
template class Uniform<mat4>;

template<typename VAR_T>
MaterialUniform<VAR_T>::MaterialUniform(const Shader *shader, const char *uniformName, const std::string &varName) :
	m_location(glGetUniformLocation(shader->getShaderProgram(), uniformName)),
	m_name(varName) {}

template<typename VAR_T>
void MaterialUniform<VAR_T>::update(const Shader *shader) const
{
	shader->setUniform(m_location, *(VAR_T*) Material::CURRENT->get(m_name));
}

template class MaterialUniform<int>;
template class MaterialUniform<float>;
template class MaterialUniform<vec2>;
template class MaterialUniform<vec3>;
template class MaterialUniform<vec4>;
template class MaterialUniform<mat4>;

SamplerUniform::SamplerUniform(const Shader *shader, const char *name, int samplerSlot) :
	m_location(glGetUniformLocation(shader->getShaderProgram(), name)),
	m_samplerSlot(samplerSlot) {}

void SamplerUniform::update(const Shader *shader) const
{
	shader->setUniform(m_location, m_samplerSlot);
}