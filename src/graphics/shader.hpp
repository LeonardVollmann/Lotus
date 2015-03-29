#ifndef SHADER_HPP
#define SHADER_HPP

#include "../maths/maths.hpp"

#include <GL/glew.h>
#include <map>
#include <string>

namespace lotus { namespace graphics {

    class Shader
    {
    private:
        std::string m_fileName;
        
        GLuint m_program;
        GLuint m_shaders[3];
        int m_numShaders;
        
        mutable std::map<std::string, GLint> m_uniforms;
    public:
        static std::string loadShader(const std::string &fileName);
        static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage);
        static GLuint createShader(const std::string &text, GLenum shaderType);
    
        Shader(const std::string &fileName);
        virtual ~Shader();
    
        void bind() const;
        void unbind() const;
        
        Shader &addVertexShader();
        Shader &addFragmentShader();
        Shader &addGeometryShader();
        Shader &compile();
        
        void addUniform(const std::string &uniform) const;
        void setUniformInteger(const std::string &uniform, int value) const;
        void setUniformFloat(const std::string &uniform, float value) const;
        void setUniformVector3f(const std::string &uniform, const maths::vec3 &value) const;
        void setUniformMatrix4f(const std::string &uniform, const maths::mat4 &value) const;
    };

} }
    
#endif