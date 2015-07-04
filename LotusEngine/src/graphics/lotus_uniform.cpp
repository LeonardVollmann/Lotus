#include "lotus_uniform.hpp"
#include "lotus_shader.hpp"

template<typename VAR_T>
VarUniform<VAR_T>::VarUniform(const Shader *shader, const char *name, unsigned char **owner, size_t varOffset) :
	m_location(glGetUniformLocation(shader->getShaderProgram(), name)),
	m_owner(owner),
	m_varOffset(varOffset) {}

template<typename VAR_T>
void VarUniform<VAR_T>::update(const Shader *shader) const
{
	shader->setUniform(m_location, *(VAR_T*) (*m_owner + m_varOffset));
}

template class VarUniform<int>;
template class VarUniform<float>;
template class VarUniform<vec2>;
template class VarUniform<vec3>;
template class VarUniform<vec4>;
template class VarUniform<mat4>;

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

template<typename VAR_T>
FunctionUniform<VAR_T>::FunctionUniform(const Shader *shader, const char *name, VAR_T (*getUniformValue)()) :
	m_location(glGetUniformLocation(shader->getShaderProgram(), name)),
	m_getUniformValue(getUniformValue) {}

template<typename VAR_T>
void FunctionUniform<VAR_T>::FunctionUniform::update(const Shader *shader) const
{
	shader->setUniform(m_location, m_getUniformValue());
}

template class FunctionUniform<int>;
template class FunctionUniform<float>;
template class FunctionUniform<vec2>;
template class FunctionUniform<vec3>;
template class FunctionUniform<vec4>;
template class FunctionUniform<mat4>;