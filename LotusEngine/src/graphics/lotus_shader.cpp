#include "lotus_shader.hpp"
#include "lotus_fileutils.hpp"
#include "lotus_stringutils.hpp"

#include <iostream>

#define GET_BOUND_INSTANCE(t) (void*) t::CURRENT

Shader::Shader(const std::string &fileName) :
	m_fileName(fileName)
{
	m_program = glCreateProgram();
}

Shader::~Shader()
{
	for (auto it = m_uniforms.begin(); it < m_uniforms.end(); it++)
	{
		delete *it;
	}
	
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

void Shader::updateUniforms() const
{
	for (auto it = m_uniforms.begin(); it < m_uniforms.end(); it++)
	{
		(*it)->update(this);
	}
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
	glUniform3f(m_uniformLocations[uniform + ".color"], baseLight.getColor().x, baseLight.getColor().y, baseLight.getColor().z);
	glUniform1f(m_uniformLocations[uniform + ".intensity"], baseLight.getIntensity());
}

void Shader::setUniformDirectionalLight(const std::string &uniform, const DirectionalLight &directionalLight) const
{
	setUniformBaseLight(uniform + ".base", BaseLight(directionalLight.getColor(), directionalLight.getIntensity()));
	glUniform3f(m_uniformLocations[uniform + ".direction"], directionalLight.getDirection().x, directionalLight.getDirection().y, directionalLight.getDirection().z);
}

void Shader::setUniformAttenuation(const std::string &uniform, const Attenuation &attenuation) const
{
	setUniformFloat(uniform + ".constant", attenuation.getConstant());
	setUniformFloat(uniform + ".linear", attenuation.getLinear());
	setUniformFloat(uniform + ".exponent", attenuation.getExponent());
}

void Shader::setUniformPointLight(const std::string &uniform, const PointLight &pointLight) const
{
	setUniformBaseLight(uniform + ".base", BaseLight(pointLight.getColor(), pointLight.getIntensity()));
	setUniformAttenuation(uniform + ".atten", pointLight.getAttenuation());
	setUniformVec3(uniform + ".pos", pointLight.getPos());
	setUniformFloat(uniform + ".range", pointLight.getRange());
}

void Shader::setUniformSpotLight(const std::string &uniform, const SpotLight &spotLight) const
{
	setUniformPointLight(uniform + ".pointLight", PointLight(spotLight.getColor(), spotLight.getIntensity(), spotLight.getAttenuation(), spotLight.getPos()));
	setUniformVec3(uniform + ".direction", spotLight.getDirection());
	setUniformFloat(uniform + ".cutoff", spotLight.getCutoff());
}

void Shader::setUniform(GLint location, const int &value) const
{
	glUniform1i(location, value);
}

void Shader::setUniform(GLint location, const float &value) const
{
	glUniform1f(location, value);
}

void Shader::setUniform(GLint location, const vec2 &value) const
{
	glUniform2f(location, value.x, value.y);
}

void Shader::setUniform(GLint location, const vec3 &value) const
{
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::setUniform(GLint location, const vec4 &value) const
{
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::setUniform(GLint location, const mat4 &value) const
{
	glUniformMatrix4fv(location, 1, GL_FALSE, value.elements);
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
			if (tokens[1] == "sampler2D")
			{
				addSampler(tokens[2]);
			}
			else
			{
				m_uniformTypes.insert(std::pair<std::string, std::string>(tokens[2], tokens[1]));
			}
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

void Shader::addAllUniforms() const
{
	for (auto it = m_uniformTypes.begin(); it != m_uniformTypes.end(); it++)
	{
		addUniform(it->first, it->second);
	}
	
	for (unsigned int i = 0; i < m_samplers.size(); i++)
	{
		m_uniforms.push_back(new SamplerUniform(this, m_samplers[i].c_str(), i));
	}
	
	m_uniformStructs.clear();
	m_uniformTypes.clear();
	m_samplers.clear();
}

void Shader::addUniform(const std::string &uniform, const std::string &type) const
{
	GLint location = glGetUniformLocation(m_program, uniform.c_str());
	m_uniformLocations.insert(std::pair<std::string, GLint>(uniform, location));
	
	std::vector<std::string> tokens = StringUtils::getTokens(uniform, "_");
	
	if (uniform == "mvp_matrix")
	{
		mat4(*getMVPMatrix)() = []()->mat4 { return Scene::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix() * Transform::CURRENT->getTransformation(); };
		m_uniforms.push_back(new FunctionUniform<mat4>(this, "mvp_matrix", getMVPMatrix));
	}
	else if (tokens[0] == "transform")
	{
		if (tokens[1] == "pos")
		{
			vec3(*getTransformPos)() = []()->vec3 { return Transform::CURRENT->getPos(); };
			m_uniforms.push_back(new FunctionUniform<vec3>(this, uniform.c_str(), getTransformPos));
		}
		else if (tokens[1] == "rot")
		{
			vec4(*getTransformRot)() = []()->vec4 { return vec4(Transform::CURRENT->getRot().x, Transform::CURRENT->getRot().y, Transform::CURRENT->getRot().z, Transform::CURRENT->getRot().w); };
			m_uniforms.push_back(new FunctionUniform<vec4>(this, uniform.c_str(), getTransformRot));
		}
		else if (tokens[1] == "scale")
		{
			vec3(*getTransformScale)() = []()->vec3 { return Transform::CURRENT->getScale(); };
			m_uniforms.push_back(new FunctionUniform<vec3>(this, uniform.c_str(), getTransformScale));
		}
		else if (tokens[1] == "modelMatrix")
		{
			mat4(*getModelMatrix)() = []()->mat4 { return Transform::CURRENT->getTransformation(); };
			m_uniforms.push_back(new FunctionUniform<mat4>(this, uniform.c_str(), getModelMatrix));
		}
	}
	else if (tokens[0] == "scene")
	{
		if (tokens[1] == "projection")
		{
			mat4(*getProjectionMatrix)() = []()->mat4 { return Scene::CURRENT->getProjection(); };
			m_uniforms.push_back(new FunctionUniform<mat4>(this, uniform.c_str(), getProjectionMatrix));
		}
	}
	else if (tokens[0] == "camera")
	{
		if (tokens[1] == "pos")
		{
			vec3(*getCameraPos)() = []()->vec3 { return Camera::CURRENT->getTransform().getPos(); };
			m_uniforms.push_back(new FunctionUniform<vec3>(this, uniform.c_str(), getCameraPos));
		}
		else if (tokens[1] == "rot")
		{
			vec4(*getCameraRot)() = []()->vec4 { return vec4(Camera::CURRENT->getTransform().getRot().x, Camera::CURRENT->getTransform().getRot().y, Camera::CURRENT->getTransform().getRot().z, Camera::CURRENT->getTransform().getRot().x); };
			m_uniforms.push_back(new FunctionUniform<vec4>(this, uniform.c_str(), getCameraRot));
		}
		else if (tokens[1] == "viewMatrix")
		{
			mat4(*getCameraViewMatrix)() = []()->mat4 { return Camera::CURRENT->getViewMatrix(); };
			m_uniforms.push_back(new FunctionUniform<mat4>(this, uniform.c_str(), getCameraViewMatrix));
		}
	}
	else if (tokens[0] == "material")
	{
		if (type == "int") m_uniforms.push_back(new MaterialUniform<int>(this, uniform.c_str(), tokens[1]));
		else if (type == "float") m_uniforms.push_back(new MaterialUniform<float>(this, uniform.c_str(), tokens[1]));
		else if (type == "vec2") m_uniforms.push_back(new MaterialUniform<vec2>(this, uniform.c_str(), tokens[1]));
		else if (type == "vec3") m_uniforms.push_back(new MaterialUniform<vec3>(this, uniform.c_str(), tokens[1]));
		else if (type == "vec4") m_uniforms.push_back(new MaterialUniform<vec4>(this, uniform.c_str(), tokens[1]));
		else if (type == "mat4") m_uniforms.push_back(new MaterialUniform<mat4>(this, uniform.c_str(), tokens[1]));
	}
	else if (tokens[0] == "light")
	{
		if (tokens[1] == "directional") m_uniforms.push_back(new StructUniform<DirectionalLight, 3, DirectionalLight::getUniformLocations>(this, uniform.c_str()));
		else if (tokens[1] == "point") m_uniforms.push_back(new StructUniform<PointLight, 7, PointLight::getUniformLocations>(this, uniform.c_str()));
		else if (tokens[1] == "spot") m_uniforms.push_back(new StructUniform<SpotLight, 9, SpotLight::getUniformLocations>(this, uniform.c_str()));
	}
}

void Shader::addSampler(const std::string &uniform)
{
	m_samplers.push_back(uniform);
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