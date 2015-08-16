#include "shaderfactory.hpp"
#include "shadersources.hpp"

namespace lotus { namespace graphics {

	const char *ShaderFactory::s_source_basic_vert = SOURCE_BASIC_VERT;
	const char *ShaderFactory::s_source_basic_frag = SOURCE_BASIC_FRAG;
	const char *ShaderFactory::s_source_forward_vert = SOURCE_FORWARD_VERT;
	const char *ShaderFactory::s_source_forward_ambient_frag = SOURCE_FORWARD_FRAG SOURCE_FORWARD_SAMPLING SOURCE_FORWARD_AMBIENT_FRAG;
	const char *ShaderFactory::s_source_forward_directional_frag = SOURCE_FORWARD_FRAG SOURCE_LIGHTING SOURCE_FORWARD_SAMPLING SOURCE_FORWARD_DIRECTIONAL_FRAG SOURCE_FORWARD_MAIN_FRAG;
	const char *ShaderFactory::s_source_forward_point_frag = SOURCE_FORWARD_FRAG SOURCE_LIGHTING SOURCE_FORWARD_SAMPLING SOURCE_FORWARD_POINT_FRAG SOURCE_FORWARD_MAIN_FRAG;
	const char *ShaderFactory::s_source_forward_spot_frag = SOURCE_FORWARD_FRAG SOURCE_LIGHTING SOURCE_FORWARD_SAMPLING SOURCE_FORWARD_SPOT_FRAG SOURCE_FORWARD_MAIN_FRAG;
	const char *ShaderFactory::s_source_batch2d_vert = SOURCE_BATCH2D_VERT;
	const char *ShaderFactory::s_source_batch2d_frag = SOURCE_BATCH2D_FRAG;

	Shader *ShaderFactory::s_basic = nullptr;
	Shader *ShaderFactory::s_forwardAmbient = nullptr;
	Shader *ShaderFactory::s_forwardDirectional = nullptr;
	Shader *ShaderFactory::s_forwardPoint = nullptr;
	Shader *ShaderFactory::s_forwardSpot = nullptr;
	Shader *ShaderFactory::s_batch2d = nullptr;

	Shader *ShaderFactory::getBasic()
	{
		if (s_basic == nullptr)
		{
			s_basic = new Shader("basicShader");
			s_basic->addVertexShader("basicVertex", s_source_basic_vert);
			s_basic->addFragmentShader("basicFragment", s_source_basic_frag);
			s_basic->compile();
		}
		
		return s_basic;
	}

	Shader *ShaderFactory::getForwardAmbient()
	{
		if (s_forwardAmbient == nullptr)
		{
			s_forwardAmbient = new Shader("forwardAmbient");
			s_forwardAmbient->addVertexShader("forwardAmbientVertex", s_source_forward_vert);
			s_forwardAmbient->addFragmentShader("forwardAmbientFragment", s_source_forward_ambient_frag);
			s_forwardAmbient->compile();
		}
			
		return s_forwardAmbient;
	}

	Shader *ShaderFactory::getForwardDirectional()
	{
		if (s_forwardDirectional == nullptr)
		{
			s_forwardDirectional = new Shader("forwardDirectional");
			s_forwardDirectional->addVertexShader("forwardDirectionalVertex", s_source_forward_vert);
			s_forwardDirectional->addFragmentShader("forwardDirectionalFragment", s_source_forward_directional_frag);
			s_forwardDirectional->compile();
		}
		
		return s_forwardDirectional;
	}

	Shader *ShaderFactory::getForwardPoint()
	{
		if (s_forwardPoint == nullptr)
		{
			s_forwardPoint = new Shader("forwardPoint");
			s_forwardPoint->addVertexShader("forwardPointVertex", s_source_forward_vert);
			s_forwardPoint->addFragmentShader("forwardPointFragment", s_source_forward_point_frag);
			s_forwardPoint->compile();
		}
		
		return s_forwardPoint;
	}

	Shader *ShaderFactory::getForwardSpot()
	{
		if (s_forwardSpot == nullptr)
		{
			s_forwardSpot = new Shader("forwardSpot");
			s_forwardSpot->addVertexShader("forwardSpotVertex", s_source_forward_vert);
			s_forwardSpot->addFragmentShader("forwardSpotFragment", s_source_forward_spot_frag);
			s_forwardSpot->compile();
		}
		
		return s_forwardSpot;
	}

	Shader *ShaderFactory::getBatch2D()
	{
		if (s_batch2d == nullptr)
		{
			s_batch2d = new Shader("batch2d");
			s_batch2d->addVertexShader("batch2dVertex", s_source_batch2d_vert);
			s_batch2d->addFragmentShader("batch2dFragment", s_source_batch2d_frag);
		}

		return s_batch2d;
	}

	void ShaderFactory::shutdown()
	{
		delete s_basic;
		delete s_forwardAmbient;
		delete s_forwardDirectional;
		delete s_forwardPoint;
		delete s_forwardSpot;
	}

} }