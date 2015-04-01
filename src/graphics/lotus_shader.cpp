#include "lotus_shader.hpp"
#include "../utils/lotus_fileutils.hpp"

#include <iostream>

namespace lotus { namespace graphics {
    
    void check_shader_error(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    GLuint create_shader(const std::string &text, GLenum shaderType);
    
    Shader::Shader(const std::string &fileName) :
        m_fileName(fileName)
    {
        m_program = glCreateProgram();

        glBindAttribLocation(m_program, 0, "vertex_pos");
        glBindAttribLocation(m_program, 1, "vertex_texCoord");
        glBindAttribLocation(m_program, 2, "vertex_normal");
    }
    
    Shader::~Shader()
    {
        for (unsigned int i = 0; i < 3; i++) {
            glDetachShader(m_program, m_shaders[i]);
            glDeleteShader(m_shaders[i]);
        }
        
        glDeleteProgram(m_program);
    }
    
    void Shader::bind() const
    {
        glUseProgram(m_program);
    }
    
    void Shader::unbind() const
    {
        glUseProgram(0);
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
    
    void Shader::setUniformVector3f(const std::string &uniform, const maths::vec3 &value) const
    {
        glUniform3f(m_uniforms[uniform], value.x, value.y, value.z);
    }
    
    void Shader::setUniformMatrix4f(const std::string &uniform, const maths::mat4 &value) const
    {   
        glUniformMatrix4fv(m_uniforms[uniform], 1, false, value.elements);
    }
    
    Shader &Shader::addVertexShader()
    {
        GLuint shader = create_shader(FileUtils::readFile("res/shaders/" + m_fileName + "-vert.glsl"), GL_VERTEX_SHADER);
        glAttachShader(m_program, shader);
        m_shaders[0] = shader;
        
        return *this;
    }
    
    Shader &Shader::addFragmentShader()
    {
        GLuint shader = create_shader(FileUtils::readFile("res/shaders/" + m_fileName + "-frag.glsl"), GL_FRAGMENT_SHADER);
        glAttachShader(m_program, shader);
        m_shaders[1] = shader;
        
        return *this;
    }
    
    Shader &Shader::addGeometryShader()
    {
        GLuint shader = create_shader(FileUtils::readFile("res/shaders/" + m_fileName + "-geom-glsl"), GL_GEOMETRY_SHADER);
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

    void check_shader_error(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
    {
        GLint success = 0;
        GLchar error[1024] = { 0 };
        
        if(isProgram) {
            glGetProgramiv(shader, flag, &success);
        } else {
            glGetShaderiv(shader, flag, &success);
        }
        
        if(success == GL_FALSE) {
            if(isProgram) {
                glGetProgramInfoLog(shader, sizeof(error), NULL, error);
            } else {
                glGetShaderInfoLog(shader, sizeof(error), NULL, error);
            }
            
            std::cerr << errorMessage << ": '" << error << "'" << std::endl;
        }
    }

    GLuint create_shader(const std::string &text, GLenum shaderType)
    {
        GLuint shader = glCreateShader(shaderType);
        if (shader == 0) {
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
    
} }