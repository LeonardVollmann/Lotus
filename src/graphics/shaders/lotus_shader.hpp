#ifndef LOTUS_SHADER_HPP_INCLUDED
#define LOTUS_SHADER_HPP_INCLUDED

#include "../lotus_camera.hpp"
#include "../lotus_material.hpp"
#include "../lotus_lighting.hpp"
#include "../layers/lotus_layer.hpp"
#include "../../maths/lotus_maths.hpp"
#include "../../core/lotus_transform.hpp"

#include <GL/glew.h>
#include <map>
#include <string>
#include <vector>

class Shader
{
public:
	static const std::string SOURCE_DIRECTORY;
	static const std::string INCLUDE_DIRECTIVE;
	static const std::string UNIFORM_DIRECTIVE;
	static const std::string STRUCT_DIRECTIVE;
	static const std::string VERT_EXTENSION;
	static const std::string FRAG_EXTENSION;
	static const std::string GEOM_EXTENSION;
protected:
	std::string															m_fileName;
	GLuint																m_program;
	GLuint																m_shaders[3];
	mutable std::map<std::string, std::string>							m_uniformTypes;
	mutable std::map<std::string, std::map<std::string, std::string>>	m_uniformStructs;
	mutable std::map<std::string, GLint>								m_uniformLocations;
public:
	virtual ~Shader();

	virtual void bind() const;

	virtual Shader &addVertexShader(const std::string &fileName);
	virtual Shader &addFragmentShader(const std::string &fileName);
	virtual Shader &addGeometryShader(const std::string &fileName);
	virtual Shader &compile();

	virtual void updateUniforms(const Transform &transform) const = 0;

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
protected:
	Shader(const std::string &fileName);
	
	std::string preprocess(const std::string &shaderText);
	
	void addAllUniforms() const;
	void addUniformStruct(const std::string &uniform, const std::map<std::string, std::string> &uniformStruct) const;
	bool isUniformStruct(const std::string &uniformType) const;
	void addUniform(const std::string &uniform) const;
	
	void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint createShader(const std::string &text, const std::string &fileName, GLenum shaderType);
};

#endif