#ifndef LOTUS_SHADER_FACTORY_HPP_INCLUDED
#define LOTUS_SHADER_FACTORY_HPP_INCLUDED

#include "shader.hpp"

namespace lotus { namespace graphics {

	class ShaderFactory
	{
	private:
		static const char *s_source_basic_vert;
		static const char *s_source_basic_frag;
		static const char *s_source_forward_vert;
		static const char *s_source_forward_ambient_frag;
		static const char *s_source_forward_directional_frag;
		static const char *s_source_forward_point_frag;
		static const char *s_source_forward_spot_frag;
		static const char *s_source_batch2d_vert;
		static const char *s_source_batch2d_frag;
		
		static Shader *s_basic;
		static Shader *s_forwardAmbient;
		static Shader *s_forwardDirectional;
		static Shader *s_forwardPoint;
		static Shader *s_forwardSpot;
		static Shader *s_batch2d;
	public:
		static Shader *getBasic();
		static Shader *getForwardAmbient();
		static Shader *getForwardDirectional();
		static Shader *getForwardPoint();
		static Shader *getForwardSpot();
		static Shader *getBatch2D();
		
		static void cleanUp();
	};

} }

#endif