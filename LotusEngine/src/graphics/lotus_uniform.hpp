#ifndef LOTUS_UNIFORM_HPP_INCLUDED
#define LOTUS_UNIFORM_HPP_INCLUDED

#include "lotus_vec2.hpp"
#include "lotus_vec3.hpp"
#include "lotus_vec4.hpp"
#include "lotus_mat4.hpp"
#include "lotus_material.hpp"

#include <GL/glew.h>
#include <string>

class Shader;

class IUniform
{
public:
	virtual ~IUniform() {}
	virtual void update(const Shader *shader) const = 0;
};

template <typename VAR_T>
class VarUniform : public IUniform
{
private:
	GLint			m_location;
	unsigned char	**m_owner;
	size_t			m_varOffset;
public:
	VarUniform(const Shader *shader, const char *name, unsigned char **owner, size_t m_varOffset);
	
	virtual void update(const Shader *shader) const final;
};

template <typename VAR_T>
class MaterialUniform : public IUniform
{
private:
	GLint		m_location;
	std::string m_name;
public:
	MaterialUniform(const Shader *shader, const char *uniformName, const std::string &varName);
	
	virtual void update(const Shader *shader) const final;
};

class SamplerUniform : public IUniform
{
private:
	GLint	m_location;
	int		m_samplerSlot;
public:
	SamplerUniform(const Shader *shader, const char *name, int samplerSlot);
	
	virtual void update(const Shader *shader) const final;
};

template <typename VAR_T>
class FunctionUniform : public IUniform
{
private:
	GLuint m_location;
	VAR_T (*m_getUniformValue)();
public:
	FunctionUniform(const Shader *shader, const char *name, VAR_T (*getUniformValue)());
	
	virtual void update(const Shader *shader) const final;
};

template <typename VAR_T, unsigned int NUM_MEMBERS, void GET_LOCATIONS(const Shader *shader, const char *name, GLuint *locations)>
class StructUniform : public IUniform
{
private:
	GLuint m_locations[NUM_MEMBERS];
public:
	StructUniform(const Shader *shader, const char *name);
	
	virtual void update(const Shader *shader) const final;
};

#endif