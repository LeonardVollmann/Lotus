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

#define SOURCE_DIRECTORY	"res/shaders/"
#define INCLUDE_DIRECTIVE	"#include"
#define	STRUCT_DIRECTIVE	"struct"
#define UNIFORM_DIRECTIVE	"uniform"
#define VERT_EXTENSION		"-vert.glsl"
#define FRAG_EXTENSION		"-frag.glsl"
#define GEOM_EXTENSION		"-geom.glsl"

class Shader
{
protected:
	std::string															m_fileName;
	GLuint																m_program;
	GLuint																m_shaders[3];
	mutable std::map<std::string, std::string>							m_uniformTypes;
	mutable std::map<std::string, std::map<std::string, std::string>>	m_uniformStructs;
	mutable std::map<std::string, GLint>								m_uniformLocations;
	mutable std::vector<IUniform*>										m_uniforms;
	mutable std::vector<std::string>									m_samplers;
public:
	virtual ~Shader();

	void bind() const;

	Shader &addVertexShader(const std::string &fileName);
	Shader &addFragmentShader(const std::string &fileName);
	Shader &addGeometryShader(const std::string &fileName);
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
	Shader(const std::string &fileName);
	
	std::string preprocess(const std::string &shaderText);
	
	void addAllUniforms() const;
	void addUniformStruct(const std::string &uniform, const std::map<std::string, std::string> &uniformStruct) const;
	bool isUniformStruct(const std::string &uniformType) const;
	void addUniform(const std::string &uniform, const std::string &type = "") const;
	void addSampler(const std::string &uniform);
	
	void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint createShader(const std::string &text, const std::string &fileName, GLenum shaderType);
};

#endif