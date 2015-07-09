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

ForwardSpot::~ForwardSpot()
{
	for (auto it = m_spotLights.begin(); it < m_spotLights.end(); it++)
	{
		delete *it;
	}
}

void ForwardSpot::addSpotLight(SpotLight *spotLight)
{
	m_spotLights.push_back(spotLight);
}