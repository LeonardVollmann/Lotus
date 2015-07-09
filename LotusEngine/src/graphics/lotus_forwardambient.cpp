#include "lotus_forwardambient.hpp"

ForwardAmbient &ForwardAmbient::getInstance()
{
	static ForwardAmbient instance;
	return instance;
}

ForwardAmbient::ForwardAmbient() :
	Shader("forward_ambient")
{
	addVertexShader("forward_shared");
	addFragmentShader(m_fileName);
	compile();
}