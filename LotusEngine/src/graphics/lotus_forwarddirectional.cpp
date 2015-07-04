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

ForwardDirectional::~ForwardDirectional()
{
	for (auto it = m_directionalLights.begin(); it < m_directionalLights.end(); it++)
	{
		delete *it;
	}
}


void ForwardDirectional::updateUniforms() const
{
	Shader::updateUniforms();
	
	setUniformVec3("camera_pos", Camera::CURRENT->getTransform().getPos());
	
	setUniformDirectionalLight("directionalLight", **m_activeDirectionalLight);
}

void ForwardDirectional::addDirectionalLight(DirectionalLight *directionalLight)
{
	m_directionalLights.push_back(directionalLight);
}