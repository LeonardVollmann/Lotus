#ifndef LOTUS_SHADER_HPP_INCLUDED
#define LOTUS_SHADER_HPP_INCLUDED

#include "../lotus_camera.hpp"
#include "../lotus_material.hpp"
#include "../layers/lotus_layer.hpp"
#include "../../maths/lotus_maths.hpp"
#include "../../core/lotus_transform.hpp"

#include <GL/glew.h>
#include <map>
#include <string>

class Shader
{
public:
	static const std::string SOURCE_DIRECTORY;
	static const std::string INCLUDE_DIRECTIVE;
	static const std::string UNIFORM_DIRECTIVE;
protected:
	std::string m_fileName;

	GLuint 		m_program;
	GLuint 		m_shaders[3];

	mutable std::map<std::string, GLint> m_uniforms;
public:
	virtual ~Shader();
	
	virtual void bind() const;

	virtual Shader &addVertexShader();
	virtual Shader &addFragmentShader();
	virtual Shader &addGeometryShader();
	virtual Shader &compile();
	
	virtual std::string preprocess(const std::string &shaderText);
	virtual void updateUniforms(const Transform &transform) const = 0;

	virtual void addUniform(const std::string &uniform) const;
	virtual void setUniformInteger(const std::string &uniform, int value) const;
	virtual void setUniformFloat(const std::string &uniform, float value) const;
	virtual void setUniformVec3(const std::string &uniform, const vec3 &value) const;
	virtual void setUniformVec4(const std::string &uniform, const vec4 &value) const;
	virtual void setUniformMat4(const std::string &uniform, const mat4 &value) const;
protected:
	Shader(const std::string &fileName);
};

#endif