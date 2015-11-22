#include "shader.hpp"
#include "../core/stringfunc.hpp"
#include "../maths/matrix.hpp"

#include <iostream>
#include <fstream>

namespace lotus
{
namespace graphics
{
ShaderResource::ShaderResource(const std::string &name,
                               const std::string &vShader,
                               const std::string &fShader,
                               const std::string &gShader)
: Resource(name)
{
	m_program = glCreateProgram();
	addShaders(name, vShader, fShader, gShader);
	compile();
}

ShaderResource::~ShaderResource()
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

std::string ShaderResource::preprocess(const std::string &shaderSource)
{
	std::string result;
	char *ctext = new char[shaderSource.size() + 1];
	strcpy(ctext, shaderSource.c_str());

	std::vector<std::string> lines;

	char *save_line;
	char *line = strtok_r(ctext, "\n", &save_line);
	while (line)
	{
		lines.push_back((std::string)line);
		std::vector<std::string> tokens = tokenize(line, ' ');

		if (tokens[0] == "uniform")
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
		else if (tokens[0] == "#include")
		{
			std::string include = preprocess(loadShaderSource((std::string)tokens[1]));
			lines.pop_back();
			lines.push_back(include);
		}

		line = strtok_r(nullptr, "\n", &save_line);
	}

	for (auto it = lines.begin(); it < lines.end(); it++)
	{
		result.append(*it + "\n");
	}

	delete[] ctext;
	return result;
}

GLuint ShaderResource::createShader(const std::string &text,
                                    const std::string &fileName,
                                    GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
	{
		std::cerr << "Error: Shader creation failed" << std::endl;
	}

	const GLchar *shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0]       = text.c_str();
	shaderSourceStringLengths[0] = (GLint)text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);
	checkShaderError(shader,
	                 GL_COMPILE_STATUS,
	                 false,
	                 "Error: Compilation of shader: '" + fileName + "' failed: ");

	return shader;
}

void ShaderResource::checkShaderError(GLuint shader,
                                      GLuint flag,
                                      bool isProgram,
                                      const std::string &errorMessage)
{
	GLint success      = 0;
	GLchar error[1024] = {0};

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
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

std::string ShaderResource::loadShaderSource(const std::string &fileName)
{
	std::string result;
	std::ifstream file;

	file.open("res/shaders/" + fileName);
	if (file.is_open())
	{
		std::string line;
		while (file.good())
		{
			getline(file, line);
			result.append(line + "\n");
		}
		file.close();
	}
	else
	{
		std::cout << "Could not load shader: "
		          << "res/shaders/" << fileName << std::endl;
	}

	return result;
}

void ShaderResource::addShaders(const std::string &name,
                                const std::string &vShader,
                                const std::string &fShader,
                                const std::string &gShader)
{
	addVertexShader(name, loadShaderSource((vShader != "" ? vShader : name) + "_vs.glsl"));
	addFragmentShader(name, loadShaderSource((fShader != "" ? fShader : name) + "_fs.glsl"));
	addGeometryShader(name, loadShaderSource((gShader != "" ? gShader : name) + "_gs.glsl"));
}

void ShaderResource::addVertexShader(const std::string &name, const std::string &source)
{
	if (source.size() == 0)
		return;
	GLuint shader = createShader(preprocess(source), name, GL_VERTEX_SHADER);
	glAttachShader(m_program, shader);
	m_shaders[0] = shader;
}

void ShaderResource::addFragmentShader(const std::string &name, const std::string &source)
{
	if (source.size() == 0)
		return;
	GLuint shader = createShader(preprocess(source), name, GL_FRAGMENT_SHADER);
	glAttachShader(m_program, shader);
	m_shaders[0] = shader;
}

void ShaderResource::addGeometryShader(const std::string &name, const std::string &source)
{
	if (source.size() == 0)
		return;
	GLuint shader = createShader(preprocess(source), name, GL_GEOMETRY_SHADER);
	glAttachShader(m_program, shader);
	m_shaders[0] = shader;
}

void ShaderResource::compile()
{
	glLinkProgram(m_program);
	checkShaderError(
	    m_program, GL_LINK_STATUS, true, "Error: Linking of Shader: '" + m_name + "' failed: ");

	glValidateProgram(m_program);
	checkShaderError(m_program,
	                 GL_VALIDATE_STATUS,
	                 true,
	                 "Error: Validation of Shader: '" + m_name + "'failed: ");

	addAllUniforms();
}

void ShaderResource::addAllUniforms() const
{
	for (auto it = m_uniformTypes.begin(); it != m_uniformTypes.end(); it++)
	{
		addUniform(it->first, it->second);
	}

	for (unsigned int i = 0; i < m_samplers.size(); i++)
	{
		m_uniforms.push_back(new SamplerUniform(this, m_samplers[i].c_str(), i));
	}

	m_uniformTypes.clear();
	m_samplers.clear();
}

void ShaderResource::addUniform(const std::string &uniform, const std::string &type) const
{
	std::vector<std::string> tokens = tokenize(uniform, '_');

	if (uniform == "mvp_matrix")
	{
		maths::mat4f (*getMVPMatrix)() = []() -> maths::mat4f
		{
			return Scene::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix() *
			       Transform::CURRENT->getTransformation();
		};
		m_uniforms.push_back(new FunctionUniform<maths::mat4f>(this, "mvp_matrix", getMVPMatrix));
	}
	else if (uniform == "vp_matrix")
	{
		maths::mat4f (*getVPMatrix)() = []() -> maths::mat4f
		{
			return Scene::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix();
		};
		m_uniforms.push_back(new FunctionUniform<maths::mat4f>(this, "vp_matrix", getVPMatrix));
	}
	else if (tokens[0] == "transform")
	{
		if (tokens[1] == "pos")
		{
			maths::vec3f (*getTransformPos)() = []() -> maths::vec3f
			{
				return Transform::CURRENT->getPos();
			};
			m_uniforms.push_back(
			    new FunctionUniform<maths::vec3f>(this, uniform.c_str(), getTransformPos));
		}
		else if (tokens[1] == "rot")
		{
			maths::vec4f (*getTransformRot)() = []() -> maths::vec4f
			{
				return maths::vec4f(Transform::CURRENT->getRot().x,
				                    Transform::CURRENT->getRot().y,
				                    Transform::CURRENT->getRot().z,
				                    Transform::CURRENT->getRot().w);
			};
			m_uniforms.push_back(
			    new FunctionUniform<maths::vec4f>(this, uniform.c_str(), getTransformRot));
		}
		else if (tokens[1] == "scale")
		{
			maths::vec3f (*getTransformScale)() = []() -> maths::vec3f
			{
				return Transform::CURRENT->getScale();
			};
			m_uniforms.push_back(
			    new FunctionUniform<maths::vec3f>(this, uniform.c_str(), getTransformScale));
		}
		else if (tokens[1] == "modelMatrix")
		{
			maths::mat4f (*getModelMatrix)() = []() -> maths::mat4f
			{
				return Transform::CURRENT->getTransformation();
			};
			m_uniforms.push_back(
			    new FunctionUniform<maths::mat4f>(this, uniform.c_str(), getModelMatrix));
		}
	}
	else if (tokens[0] == "scene")
	{
		if (tokens[1] == "projection")
		{
			maths::mat4f (*getProjectionMatrix)() = []() -> maths::mat4f
			{
				return Scene::CURRENT->getProjection();
			};
			m_uniforms.push_back(
			    new FunctionUniform<maths::mat4f>(this, uniform.c_str(), getProjectionMatrix));
		}
	}
	else if (tokens[0] == "camera")
	{
		if (tokens[1] == "pos")
		{
			maths::vec3f (*getCameraPos)() = []() -> maths::vec3f
			{
				return Camera::CURRENT->getTransform().getPos();
			};
			m_uniforms.push_back(
			    new FunctionUniform<maths::vec3f>(this, uniform.c_str(), getCameraPos));
		}
		else if (tokens[1] == "rot")
		{
			maths::vec4f (*getCameraRot)() = []() -> maths::vec4f
			{
				return maths::vec4f(Camera::CURRENT->getTransform().getRot().x,
				                    Camera::CURRENT->getTransform().getRot().y,
				                    Camera::CURRENT->getTransform().getRot().z,
				                    Camera::CURRENT->getTransform().getRot().x);
			};
			m_uniforms.push_back(
			    new FunctionUniform<maths::vec4f>(this, uniform.c_str(), getCameraRot));
		}
		else if (tokens[1] == "viewMatrix")
		{
			maths::mat4f (*getCameraViewMatrix)() = []() -> maths::mat4f
			{
				return Camera::CURRENT->getViewMatrix();
			};
			m_uniforms.push_back(
			    new FunctionUniform<maths::mat4f>(this, uniform.c_str(), getCameraViewMatrix));
		}
	}
	else if (tokens[0] == "material")
	{
		if (type == "int")
			m_uniforms.push_back(new MaterialUniform<int>(this, uniform.c_str(), tokens[1]));
		else if (type == "float")
			m_uniforms.push_back(new MaterialUniform<float>(this, uniform.c_str(), tokens[1]));
		else if (type == "Vector2f")
			m_uniforms.push_back(
			    new MaterialUniform<maths::vec2f>(this, uniform.c_str(), tokens[1]));
		else if (type == "Vector3f")
			m_uniforms.push_back(
			    new MaterialUniform<maths::vec3f>(this, uniform.c_str(), tokens[1]));
		else if (type == "Vector4f")
			m_uniforms.push_back(
			    new MaterialUniform<maths::vec4f>(this, uniform.c_str(), tokens[1]));
		else if (type == "Matrix4f")
			m_uniforms.push_back(
			    new MaterialUniform<maths::mat4f>(this, uniform.c_str(), tokens[1]));
	}
	else if (tokens[0] == "light")
	{
		if (tokens[1] == "ambient")
			m_uniforms.push_back(
			    new StructUniform<AmbientLight, 1, AmbientLight::getUniformLocations>(this,
			                                                                          uniform));
		else if (tokens[1] == "directional")
			m_uniforms.push_back(
			    new StructUniform<DirectionalLight, 3, DirectionalLight::getUniformLocations>(
			        this, uniform));
		else if (tokens[1] == "point")
			m_uniforms.push_back(
			    new StructUniform<PointLight, 7, PointLight::getUniformLocations>(this, uniform));
		else if (tokens[1] == "spot")
			m_uniforms.push_back(
			    new StructUniform<SpotLight, 9, SpotLight::getUniformLocations>(this, uniform));
	}
}

void ShaderResource::addSampler(const std::string &uniform)
{
	m_samplers.push_back(uniform);
}

void Shader::initShaders()
{
	ResourceManager::create<ShaderResource>(
	    "forward_ambient", false, "forward", "forward_ambient");
	ResourceManager::create<ShaderResource>(
	    "forward_directional", false, "forward", "forward_directional");
	ResourceManager::create<ShaderResource>(
	    "forward_point", false, "forward", "forward_point");
	ResourceManager::create<ShaderResource>("forward_spot", false, "forward", "forward_spot");
}

Shader::Shader(const std::string &name)
{
	m_shaderResource = ResourceManager::get<ShaderResource>(name);
}

Shader::~Shader()
{
	m_shaderResource->removeReference();
}

void Shader::bind() const
{
	glUseProgram(m_shaderResource->getShaderProgram());
}

void Shader::updateUniforms() const
{
	for (auto it = m_shaderResource->m_uniforms.begin(); it < m_shaderResource->m_uniforms.end();
	     it++)
	{
		(*it)->update(this);
	}
}

void Shader::setUniform(GLint location, const int &value) const
{
	glUniform1i(location, value);
}

void Shader::setUniform(GLint location, const float &value) const
{
	glUniform1f(location, value);
}

void Shader::setUniform(GLint location, const maths::vec2f &value) const
{
	glUniform2f(location, value.x, value.y);
}

void Shader::setUniform(GLint location, const maths::vec3f &value) const
{
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::setUniform(GLint location, const maths::vec4f &value) const
{
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::setUniform(GLint location, const maths::mat4f &value) const
{
	glUniformMatrix4fv(location, 1, GL_FALSE, value.m);
}

} // namespace graphics
} // namespace lotus