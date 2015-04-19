#include "lotus_shader.hpp"
#include "../../utils/lotus_fileutils.hpp"

#include <iostream>

const std::string Shader::SOURCE_DIRECTORY = "res/shaders/";
const std::string Shader::INCLUDE_DIRECTIVE = "#include";
const std::string Shader::UNIFORM_DIRECTIVE = "uniform";

void check_shader_error(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
GLuint create_shader(const std::string &text, GLenum shaderType);

Shader::Shader(const std::string &fileName) :
	m_fileName(fileName)
{
	m_program = glCreateProgram();
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < 3; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}

void Shader::bind() const
{
	glUseProgram(m_program);
}

Shader &Shader::addVertexShader()
{
	std::string shaderText = preprocess(FileUtils::readFile(SOURCE_DIRECTORY + m_fileName + "-vert.glsl"));
	GLuint shader = create_shader(shaderText, GL_VERTEX_SHADER);
	glAttachShader(m_program, shader);
	m_shaders[0] = shader;

	return *this;
}

Shader &Shader::addFragmentShader()
{
	std::string shaderText = preprocess(FileUtils::readFile(SOURCE_DIRECTORY + m_fileName + "-frag.glsl"));
	GLuint shader = create_shader(shaderText, GL_FRAGMENT_SHADER);
	glAttachShader(m_program, shader);
	m_shaders[1] = shader;

	return *this;
}

Shader &Shader::addGeometryShader()
{
	std::string shaderText = preprocess(FileUtils::readFile(SOURCE_DIRECTORY + m_fileName + "-geom.glsl"));
	GLuint shader = create_shader(shaderText, GL_GEOMETRY_SHADER);
	glAttachShader(m_program, shader);
	m_shaders[2] = shader;

	return *this;
}

Shader &Shader::compile()
{
	glLinkProgram(m_program);
	check_shader_error(m_program, GL_LINK_STATUS, true, "Error: Shader linking failed: ");

	glValidateProgram(m_program);
	check_shader_error(m_program, GL_VALIDATE_STATUS, true, "Error: Shader validation failed: ");

	return *this;
}

std::string Shader::preprocess(const std::string &shaderText)
{
	std::string result;
	char *ctext = new char[shaderText.size() + 1];
	strcpy(ctext, shaderText.c_str());
	
	std::vector<std::string> lines;
	
	char *save_line;
	char *line = strtok_r(ctext, "\n", &save_line);
	while (line)
	{
		lines.push_back((std::string) line);
		std::vector<char*> tokens;
		
		char *save_token;
		char *token = strtok_r(line, " ", &save_token);
		while (token)
		{
			tokens.push_back(token);
			token = strtok_r(nullptr, " ", &save_token);
		}
		
		if (tokens[0] == INCLUDE_DIRECTIVE)
		{
			std::string include = preprocess(FileUtils::readFile(SOURCE_DIRECTORY + (std::string) tokens[1]));
			lines.pop_back();
			lines.push_back(include);
		}
		
		line = strtok_r(nullptr, "\n", &save_line);
	}
	
	for (auto it = lines.begin(); it < lines.end(); it++)
	{
		result.append(*it + "\n");
	}
	
	delete ctext;
	return result;
}

void Shader::addUniform(const std::string &uniform) const
{
	GLint location = glGetUniformLocation(m_program, uniform.c_str());

	m_uniforms.insert(std::pair<std::string, GLint>(uniform, location));
}

void Shader::setUniformInteger(const std::string &uniform, int value) const
{
	glUniform1i(m_uniforms[uniform], value);
}

void Shader::setUniformFloat(const std::string &uniform, float value) const
{
	glUniform1f(m_uniforms[uniform], value);
}

void Shader::setUniformVec3(const std::string &uniform, const vec3 &value) const
{
	glUniform3f(m_uniforms[uniform], value.x, value.y, value.z);
}

void Shader::setUniformVec4(const std::string &uniform, const vec4 &value) const
{
	glUniform4f(m_uniforms[uniform], value.x, value.y, value.z, value.w);
}

void Shader::setUniformMat4(const std::string &uniform, const mat4 &value) const
{
	glUniformMatrix4fv(m_uniforms[uniform], 1, false, value.elements);
}

void check_shader_error(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if(isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if(success == GL_FALSE)
	{
		if(isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << error << std::endl;
	}
}

GLuint create_shader(const std::string &text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
	{
		std::cerr << "Error: Shader creation failed" << std::endl;
	}

	const GLchar *shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = (GLint)text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);
	check_shader_error(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}