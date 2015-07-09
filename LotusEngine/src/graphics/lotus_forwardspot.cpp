#include "lotus_forwardspot.hpp"

ForwardSpot &ForwardSpot::getInstance()
{
	static ForwardSpot instance;
	return instance;
}

ForwardSpot::ForwardSpot() :
	Shader("forward_spot")
{
	addVertexShader("forward_shared");
	addFragmentShader(m_fileName);
	compile();
}