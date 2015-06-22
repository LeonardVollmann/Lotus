#ifndef LOTUS_UNIFORM_HPP_INCLUDED
#define LOTUS_UNIFORM_HPP_INCLUDED

#include "lotus_vec2.hpp"
#include "lotus_vec3.hpp"
#include "lotus_vec4.hpp"
#include "lotus_mat4.hpp"
#include "lotus_material.hpp"

#include <GL/glew.h>

class Shader;

class IUniform
{
public:
	virtual void update(Shader *shader) = 0;
};

template<typename VAR_T>
class Uniform : public IUniform
{
private:
	GLint		m_location;
	void		**m_owner;
	size_t		m_varOffset;
public:
	Uniform(const Shader *shader, const char *name, void **owner, size_t m_varOffset);
	
	virtual void update(Shader *shader) const final;
};

#endif