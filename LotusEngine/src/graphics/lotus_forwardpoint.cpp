#include "lotus_forwardpoint.hpp"

ForwardPoint &ForwardPoint::getInstance()
{
	static ForwardPoint instance;
	return instance;
}

ForwardPoint::ForwardPoint() :
Shader("forward_point")
{
	addVertexShader("forward_shared");
	addFragmentShader(m_fileName);
	compile();
}