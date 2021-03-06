#pragma once

#include "uniform.hpp"
#include "../camera.hpp"
#include "../material.hpp"
#include "../lighting.hpp"
#include "../scene.hpp"
#include "../../core/transform.hpp"
#include "../../maths/types.hpp"

#include <GL/glew.h>
#include <map>
#include <string>
#include <vector>

namespace lotus
{
namespace graphics
{

class Shader
{
private:
	std::string m_name;
	GLuint m_program;
	GLuint m_shaders[3];
	mutable std::map<std::string, std::string> m_uniformTypes;
	mutable std::vector<IUniform *> m_uniforms;
	mutable std::vector<std::string> m_samplers;

public:
	Shader(const std::string &name,
	       const std::string &vShader = "",
	       const std::string &fShader = "",
	       const std::string &gShader = "");
	virtual ~Shader();

	inline GLuint getShaderProgram() const { return m_program; }

	void bind() const;
	void updateUniforms() const;

	void setUniform(GLint location, const int &value) const;
	void setUniform(GLint location, const float &value) const;
	void setUniform(GLint location, const maths::vec2f &value) const;
	void setUniform(GLint location, const maths::vec3f &value) const;
	void setUniform(GLint location, const maths::vec4f &value) const;
	void setUniform(GLint location, const maths::mat4f &value) const;

private:
	std::string preprocess(const std::string &shaderSource);

	GLuint createShader(const std::string &text, const std::string &fileName, GLenum shaderType);
	void
	checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage);
	std::string loadShaderSource(const std::string &fileName);
	void addShaders(const std::string &vShader,
	                const std::string &fShader,
	                const std::string &gShader);
	void addVertexShader(const std::string &name);
	void addFragmentShader(const std::string &name);
	void addGeometryShader(const std::string &name);

	void compile();

	void addAllUniforms() const;
	void addUniform(const std::string &uniform, const std::string &type = "") const;
	void addSampler(const std::string &uniform);
};

} // namespace graphics
} // namespace lotus