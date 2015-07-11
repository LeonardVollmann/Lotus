#ifndef LOTUS_SHADER_HPP_INCLUDED
#define LOTUS_SHADER_HPP_INCLUDED

#include "camera.hpp"
#include "material.hpp"
#include "lighting.hpp"
#include "scene.hpp"
#include "maths.hpp"
#include "transform.hpp"
#include "uniform.hpp"

#include <GL/glew.h>
#include <map>
#include <string>
#include <vector>

namespace lotus { namespace graphics {

	class Shader
	{
	friend class ShaderFactory;
	protected:
		std::string															m_name;
		GLuint																m_program;
		GLuint																m_shaders[3];
		mutable std::map<std::string, std::string>							m_uniformTypes;
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
		
		void setUniform(GLint location, const int &value) const;
		void setUniform(GLint location, const float &value) const;
		void setUniform(GLint location, const maths::vec2 &value) const;
		void setUniform(GLint location, const maths::vec3 &value) const;
		void setUniform(GLint location, const maths::vec4 &value) const;
		void setUniform(GLint location, const maths::mat4 &value) const;
		
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

} }

#endif