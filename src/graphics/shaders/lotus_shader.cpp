#include "lotus_shader.hpp"
#include "../../utils/lotus_fileutils.hpp"
#include "../../utils/lotus_stringutils.hpp"

#include <iostream>

const std::string Shader::SOURCE_DIRECTORY = "res/shaders/";
const std::string Shader::INCLUDE_DIRECTIVE = "#include";
const std::string Shader::UNIFORM_DIRECTIVE = "uniform";
const std::string Shader::STRUCT_DIRECTIVE = "struct";
const std::string Shader::VERT_EXTENSION = "-vert.glsl";
const std::string Shader::FRAG_EXTENSION = "-frag.glsl";
const std::string Shader::GEOM_EXTENSION = "-geom.glsl";

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

Shader &Shader::addVertexShader(const std::string &fileName)
{
	std::string shaderText = preprocess(FileUtils::readFile(SOURCE_DIRECTORY + fileName + VERT_EXTENSION));
	GLuint shader = createShader(shaderText, m_fileName + VERT_EXTENSION, GL_VERTEX_SHADER);
	glAttachShader(m_program, shader);
	m_shaders[0] = shader;

	return *this;
}

Shader &Shader::addFragmentShader(const std::string &fileName)
{
	std::string shaderText = preprocess(FileUtils::readFile(SOURCE_DIRECTORY + fileName + FRAG_EXTENSION));
	GLuint shader = createShader(shaderText, m_fileName + FRAG_EXTENSION, GL_FRAGMENT_SHADER);
	glAttachShader(m_program, shader);
	m_shaders[1] = shader;

	return *this;
}

Shader &Shader::addGeometryShader(const std::string &fileName)
{
	std::string shaderText = preprocess(FileUtils::readFile(SOURCE_DIRECTORY + fileName + GEOM_EXTENSION));
	GLuint shader = createShader(shaderText, m_fileName + GEOM_EXTENSION, GL_GEOMETRY_SHADER);
	glAttachShader(m_program, shader);
	m_shaders[2] = shader;

	return *this;
}

Shader &Shader::compile()
{
	glLinkProgram(m_program);
	checkShaderError(m_program, GL_LINK_STATUS, true, "Error: Linking of Shader: '" + m_fileName + "' failed: ");

	glValidateProgram(m_program);
	checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Validation of Shader: '" + m_fileName + "'failed: ");
	
	addAllUniforms();

	return *this;
}

void Shader::setUniformInteger(const std::string &uniform, int value) const
{
	glUniform1i(m_uniformLocations[uniform], value);
}

void Shader::setUniformFloat(const std::string &uniform, float value) const
{
	glUniform1f(m_uniformLocations[uniform], value);
}

void Shader::setUniformVec3(const std::string &uniform, const vec3 &value) const
{
	glUniform3f(m_uniformLocations[uniform], value.x, value.y, value.z);
}

void Shader::setUniformVec4(const std::string &uniform, const vec4 &value) const
{
	glUniform4f(m_uniformLocations[uniform], value.x, value.y, value.z, value.w);
}

void Shader::setUniformMat4(const std::string &uniform, const mat4 &value) const
{
	glUniformMatrix4fv(m_uniformLocations[uniform], 1, false, value.elements);
}

void Shader::setUniformBaseLight(const std::string &uniform, const BaseLight &baseLight) const
{
	glUniform3f(m_uniformLocations[uniform + ".color"], baseLight.color.x, baseLight.color.y, baseLight.color.z);
	glUniform1f(m_uniformLocations[uniform + ".intensity"], baseLight.intensity);
}

void Shader::setUniformDirectionalLight(const std::string &uniform, const DirectionalLight &directionalLight) const
{
	setUniformBaseLight(uniform + ".base", directionalLight.base);
	glUniform3f(m_uniformLocations[uniform + ".direction"], directionalLight.direction.x, directionalLight.direction.y, directionalLight.direction.z);
}

void Shader::setUniformAttenuation(const std::string &uniform, const Attenuation &attenuation) const
{
	setUniformFloat(uniform + ".constant", attenuation.constant);
	setUniformFloat(uniform + ".linear", attenuation.linear);
	setUniformFloat(uniform + ".exponent", attenuation.exponent);
}

void Shader::setUniformPointLight(const std::string &uniform, const PointLight &pointLight) const
{
	setUniformBaseLight(uniform + ".base", pointLight.base);
	setUniformAttenuation(uniform + ".atten", pointLight.atten);
	setUniformVec3(uniform + ".pos", pointLight.pos);
	setUniformFloat(uniform + ".range", pointLight.range);
}

void Shader::setUniformSpotLight(const std::string &uniform, const SpotLight &spotLight) const
{
	setUniformPointLight(uniform + ".pointLight", spotLight.pointLight);
	setUniformVec3(uniform + ".direction", spotLight.direction);
	setUniformFloat(uniform + ".cutoff", spotLight.cutoff);
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
		std::vector<std::string> tokens = StringUtils::getTokens(line, " ");
		
		if (tokens[0] == INCLUDE_DIRECTIVE)
		{
			std::string include = preprocess(FileUtils::readFile(SOURCE_DIRECTORY + (std::string) tokens[1]));
			lines.pop_back();
			lines.push_back(include);
		}
		else if (tokens[0] == UNIFORM_DIRECTIVE)
		{
			tokens[2].pop_back();
			m_uniformTypes.insert(std::pair<std::string, std::string>(tokens[2], tokens[1]));
		}
		else if (tokens[0] == STRUCT_DIRECTIVE)
		{
			std::string structName = tokens[1];
			std::map<std::string, std::string> uniformStruct;
			while (tokens[0] != "};")
			{
				line = strtok_r(nullptr, "\n", &save_line);
				if (!line)
				{
					std::cerr << "ERROR: Unterminated uniform struct detected" << std::endl;
					return result;
				}
				lines.push_back((std::string) line);
				tokens = StringUtils::getTokens((std::string)line, " ");
				
				for (auto it = tokens.begin(); it < tokens.end(); it++)
				{
					StringUtils::removeWhiteSpace(*it);
				}
				
				if (tokens.size() > 1)
				{
					tokens[1].pop_back();
					uniformStruct.insert(std::pair<std::string, std::string>(tokens[1], tokens[0]));
				}
			}
			
			if (m_uniformStructs.find(structName) == m_uniformStructs.end())
			{
				m_uniformStructs.insert(std::pair<std::string, std::map<std::string, std::string>>(structName, uniformStruct));
			}
		}
		
		line = strtok_r(nullptr, "\n", &save_line);
	}
	
	for (auto it = lines.begin(); it < lines.end(); it++)
	{
		result.append(*it + "\n");
	}
	
//	for (auto it = m_uniformStructs.begin(); it != m_uniformStructs.end(); it++)
//	{
//		std::cout << it->first << std::endl;
//		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
//		{
//			std::cout << "- " << it2->first + " " << it2->second << std::endl;
//		}
//	}
	
	delete ctext;
	return result;
}

void Shader::addAllUniforms() const
{
	for (auto it = m_uniformTypes.begin(); it != m_uniformTypes.end(); it++)
	{
		if (isUniformStruct(it->second))
		{
			addUniformStruct(it->first, m_uniformStructs.at(it->second));
		}
		else
		{
			addUniform(it->first);
		}
	}
}

void Shader::addUniformStruct(const std::string &uniform, const std::map<std::string, std::string> &uniformStruct) const
{
	std::string prefix = uniform + ".";
	for (auto it = uniformStruct.begin(); it != uniformStruct.end(); it++)
	{
		if (isUniformStruct(it->second))
		{
			addUniformStruct(prefix + it->first, m_uniformStructs.at(it->second));
		}
		else
		{
			addUniform(prefix + it->first);
		}
	}
}

bool Shader::isUniformStruct(const std::string &uniformType) const
{
	return m_uniformStructs.find(uniformType) != m_uniformStructs.end();
}

void Shader::addUniform(const std::string &uniform) const
{
	GLint location = glGetUniformLocation(m_program, uniform.c_str());
	
	m_uniformLocations.insert(std::pair<std::string, GLint>(uniform, location));
}

void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
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

GLuint Shader::createShader(const std::string &text, const std::string &fileName, GLenum shaderType)
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
	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Compilation of shader: '" + fileName + "' failed: ");
	
	return shader;
}