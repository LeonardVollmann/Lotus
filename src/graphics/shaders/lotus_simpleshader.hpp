#ifndef LOTUS_SIMPLE_SHADER_HPP_INCLUDED
#define LOTUS_SIMPLE_SHADER_HPP_INCLUDED

#include "lotus_shader.hpp"

namespace lotus { namespace graphics { 

	class SimpleShader : public Shader
	{
	public:
		SimpleShader();

		virtual void updateUniforms(const Transform &transform, const Material &material, const Camera &camera, const maths::mat4 &projection) const override;
	};

} }

#endif