#ifndef LOTUS_SHADER_HPP_INCLUDED
#define LOTUS_SHADER_HPP_INCLUDED

#include "lotus_lighting.hpp"
#include "../maths/lotus_maths.hpp"

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
        
        mutable std::map<std::string, GLint> m_uniforms;
    public:
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
        void setUniformVec3(const std::string &uniform, const maths::vec3 &value) const;
        void setUniformVec4(const std::string &uniform, const maths::vec4 &value) const;
        void setUniformMat4(const std::string &uniform, const maths::mat4 &value) const;
        void setUniformBaseLight(const std::string &uniform, const BaseLight &baseLight);
        void setUniformDirectionalLight(const std::string &uniform, const DirectionalLight &directionalLight);
    };

} }
    
#endif