#include "lotus_uniform.hpp"
#include "lotus_shader.hpp"

template<typename VAR_T>
Uniform<VAR_T>::Uniform(const Shader *shader, const char *name, void **owner, size_t varOffset) :
	m_location(glGetUniformLocation(shader->getShaderProgram(), name)),
	m_owner(owner),
	m_varOffset(varOffset) {}

template<typename VAR_T>
void Uniform<VAR_T>::update(Shader *shader) const
{
	// Set shader uniform with value stored at *m_owner + varOffset
}