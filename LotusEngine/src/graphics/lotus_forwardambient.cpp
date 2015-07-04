#include "lotus_forwardambient.hpp"

ForwardAmbient &ForwardAmbient::getInstance()
{
	static ForwardAmbient instance;
	return instance;
}

ForwardAmbient::ForwardAmbient() :
	Shader("forward_ambient"),
	m_ambientLight(0.1f, 0.1f, 0.1f)
{
	addVertexShader("forward_shared");
	addFragmentShader(m_fileName);
	compile();
}

void ForwardAmbient::updateUniforms() const
{
	Shader::updateUniforms();
	
	setUniformVec3("camera_pos", Camera::CURRENT->getTransform().getPos());

	setUniformVec3("ambientLight", m_ambientLight);
}