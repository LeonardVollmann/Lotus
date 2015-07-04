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

ForwardPoint::~ForwardPoint()
{
	for (auto it = m_pointLights.begin(); it < m_pointLights.end(); it++)
	{
		delete *it;
	}
}


void ForwardPoint::updateUniforms() const
{
	Shader::updateUniforms();
	
	setUniformVec3("camera_pos", Camera::CURRENT->getTransform().getPos());

	setUniformPointLight("pointLight", **m_activePointLight);
}

void ForwardPoint::addPointLight(PointLight *pointLight)
{
	m_pointLights.push_back(pointLight);
}