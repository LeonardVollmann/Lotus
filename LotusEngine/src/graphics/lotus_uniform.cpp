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
//	shader->setUniform(m_location, *(VAR_T*) (*m_owner + m_varOffset));
}

template class Uniform<int>;
template class Uniform<float>;
template class Uniform<vec2>;
template class Uniform<vec3>;
template class Uniform<vec4>;
template class Uniform<mat4>;