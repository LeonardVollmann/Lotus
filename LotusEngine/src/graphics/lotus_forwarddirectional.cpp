#include "lotus_forwarddirectional.hpp"

ForwardDirectional &ForwardDirectional::getInstance()
{
	static ForwardDirectional instance;
	return instance;
}

ForwardDirectional::ForwardDirectional() :
	Shader("forward_directional")
{
	addVertexShader("forward_shared");
	addFragmentShader(m_fileName);
	compile();
}