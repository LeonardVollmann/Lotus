#ifndef LOTUS_SHADER_HPP_INCLUDED
#define LOTUS_SHADER_HPP_INCLUDED

#include "lotus_camera.hpp"
#include "lotus_material.hpp"
#include "lotus_lighting.hpp"
#include "lotus_scene.hpp"
#include "lotus_maths.hpp"
#include "lotus_transform.hpp"
#include "lotus_uniform.hpp"

#include <GL/glew.h>
#include <map>
#include <string>
#include <vector>

class Shader
{
friend class ShaderFactory;
protected:
	std::string															m_name;
	GLuint																m_program;
	GLuint																m_shaders[3];
	mutable std::map<std::string, std::string>							m_uniformTypes;
	mutable std::map<std::string, GLint>								m_uniformLocations;
	mutable std::vector<IUniform*>										m_uniforms;
	mutable std::vector<std::string>									m_samplers;
public:
	virtual ~Shader();

	void bind() const;

	Shader &addVertexShader(const std::string &name, const std::string &source);
	Shader &addFragmentShader(const std::string &name, const std::string &source);
	Shader &addGeometryShader(const std::string &name, const std::string &source);
	Shader &compile();

	virtual void updateUniforms() const;
	
	virtual void setUniformInteger(const std::string &uniform, int value) const;
	virtual void setUniformFloat(const std::string &uniform, float value) const;
	virtual void setUniformVec3(const std::string &uniform, const vec3 &value) const;
	virtual void setUniformVec4(const std::string &uniform, const vec4 &value) const;
	virtual void setUniformMat4(const std::string &uniform, const mat4 &value) const;
	virtual void setUniformBaseLight(const std::string &uniform, const BaseLight &baseLight) const;
	virtual void setUniformDirectionalLight(const std::string &uniform, const DirectionalLight &directionalLight) const;
	virtual void setUniformAttenuation(const std::string &uniform, const Attenuation &attenuation) const;
	virtual void setUniformPointLight(const std::string &uniform, const PointLight &pointLight) const;
	virtual void setUniformSpotLight(const std::string &uniform, const SpotLight &spotLight) const;
	
	void setUniform(GLint location, const int &value) const;
	void setUniform(GLint location, const float &value) const;
	void setUniform(GLint location, const vec2 &value) const;
	void setUniform(GLint location, const vec3 &value) const;
	void setUniform(GLint location, const vec4 &value) const;
	void setUniform(GLint location, const mat4 &value) const;
	
	inline GLuint getShaderProgram() const { return m_program; }
protected:
	Shader(const std::string &name);
	
	std::string preprocess(const std::string &shaderText);
	
	void addAllUniforms() const;
	void addUniform(const std::string &uniform, const std::string &type = "") const;
	void addSampler(const std::string &uniform);
	
	std::vector<std::string> tokenizeString(const std::string &string, const std::string &delim) const;
	std::string &removeWhiteSpace(std::string &string) const;
	
	void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint createShader(const std::string &text, const std::string &fileName, GLenum shaderType);
};

#endif