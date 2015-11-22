#pragma once

#include "material.hpp"

#include <GL/glew.h>
#include <string>

namespace lotus
{
namespace graphics
{

class Shader;
class ShaderResource;

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
	GLint m_location;
	unsigned char **m_owner;
	size_t m_varOffset;

public:
	VarUniform(const ShaderResource *shader,
	           const char *name,
	           unsigned char **owner,
	           size_t m_varOffset);

	virtual void update(const Shader *shader) const final;
};

template <typename VAR_T>
class MaterialUniform : public IUniform
{
private:
	GLint m_location;
	std::string m_name;

public:
	MaterialUniform(const ShaderResource *shader,
	                const char *uniformName,
	                const std::string &varName);

	virtual void update(const Shader *shader) const final;
};

class SamplerUniform : public IUniform
{
private:
	GLint m_location;
	int m_samplerSlot;

public:
	SamplerUniform(const ShaderResource *shader, const char *name, int samplerSlot);

	virtual void update(const Shader *shader) const final;
};

template <typename VAR_T>
class FunctionUniform : public IUniform
{
private:
	GLuint m_location;
	VAR_T (*m_getUniformValue)();

public:
	FunctionUniform(const ShaderResource *shader, const char *name, VAR_T (*getUniformValue)());

	virtual void update(const Shader *shader) const final;
};

template <typename VAR_T,
          unsigned int NUM_MEMBERS,
          void GET_LOCATIONS(
              const ShaderResource *shader, const std::string &name, GLuint *locations)>
class StructUniform : public IUniform
{
private:
	GLuint m_locations[NUM_MEMBERS];

public:
	StructUniform(const ShaderResource *shader, const std::string &name);

	virtual void update(const Shader *shader) const final;
};

} // namespace graphics
} // namespace lotus