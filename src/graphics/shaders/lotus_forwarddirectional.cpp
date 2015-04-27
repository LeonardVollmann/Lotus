#include "lotus_forwarddirectional.hpp"

ForwardDirectional &ForwardDirectional::getInstance()
{
	static ForwardDirectional instance;
	return instance;
}

ForwardDirectional::ForwardDirectional() :
	Shader("forward/directional")
{
	addVertexShader("forward/shared");
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


void ForwardDirectional::updateUniforms(const Transform &transform) const
{
	mat4 transformation = transform.getTransformation();
	setUniformMat4("mvp_matrix", Layer::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix() * transformation);
	setUniformMat4("ml_matrix", transformation);
	
	setUniformVec3("cameraPos", Camera::CURRENT->getTransform().getPos());
	
	setUniformVec4("baseColor", Material::CURRENT->getVec4("color"));
	setUniformFloat("specularIntensity", Material::CURRENT->getFloat("specularIntensity"));
	setUniformFloat("specularPower", Material::CURRENT->getFloat("specularPower"));
	
	setUniformDirectionalLight("directionalLight", **m_activeDirectionalLight);
}

void ForwardDirectional::addDirectionalLight(DirectionalLight *directionalLight)
{
	m_directionalLights.push_back(directionalLight);
}