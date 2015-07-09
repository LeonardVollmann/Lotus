#include "lotus_simpleshader.hpp"

SimpleShader &SimpleShader::getInstance()
{
	static SimpleShader instance;
	return instance;
}

SimpleShader::SimpleShader() :
	Shader("simple")
{
	addVertexShader(m_fileName);
	addFragmentShader(m_fileName);
	compile();
}