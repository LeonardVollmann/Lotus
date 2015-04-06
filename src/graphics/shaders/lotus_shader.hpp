#ifndef LOTUS_SHADER_HPP_INCLUDED
#define LOTUS_SHADER_HPP_INCLUDED

#include "../lotus_camera.hpp"
#include "../lotus_material.hpp"
#include "../../maths/lotus_maths.hpp"
#include "../../core/lotus_transform.hpp"

#include <GL/glew.h>
#include <map>
#include <string>

namespace lotus { namespace graphics {

    class Shader
    {
    protected:
        std::string m_fileName;
        
        GLuint m_program;
        GLuint m_shaders[3];
        
        mutable std::map<std::string, GLint> m_uniforms;
    public:
        Shader(const std::string &fileName);
        virtual ~Shader();
    
        virtual void bind() const;
        virtual void unbind() const;
        
        virtual Shader &addVertexShader();
        virtual Shader &addFragmentShader();
        virtual Shader &addGeometryShader();
        virtual Shader &compile();

        virtual void updateUniforms(const Transform &transform, const Material &material, const Camera &camera, const maths::mat4 &projection) const = 0;

        virtual void addUniform(const std::string &uniform) const;
        virtual void setUniformInteger(const std::string &uniform, int value) const;
        virtual void setUniformFloat(const std::string &uniform, float value) const;
        virtual void setUniformVec3(const std::string &uniform, const maths::vec3 &value) const;
        virtual void setUniformVec4(const std::string &uniform, const maths::vec4 &value) const;
        virtual void setUniformMat4(const std::string &uniform, const maths::mat4 &value) const;
    };

} }
    
#endif