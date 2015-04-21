#include "lotus_forwarddirectional.hpp"

ForwardDirectional &ForwardDirectional::getInstance()
{
	static ForwardDirectional instance;
	return instance;
}

ForwardDirectional::ForwardDirectional() :
	Shader("forwarddirectional")
{
	addVertexShader();
	addFragmentShader();
	compile();
	
	addUniform("pr_matrix");
	addUniform("vw_matrix");
	addUniform("ml_matrix");
	
	addUniform("cameraPos");
	
	addUniform("baseColor");
	addUniform("specularIntensity");
	addUniform("specularPower");
	
	addUniform("directionalLight.base.color");
	addUniform("directionalLight.base.intensity");
	addUniform("directionalLight.direction");
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
	setUniformMat4("pr_matrix", Layer::CURRENT->getProjection());
	setUniformMat4("vw_matrix", Camera::CURRENT->getViewMatrix());
	setUniformMat4("ml_matrix", transform.getTransformation());
	
	setUniformVec3("cameraPos", Camera::CURRENT->getTransform().getPos());
	
	setUniformVec4("baseColor", Material::CURRENT->getColor());
	setUniformFloat("specularIntensity", Material::CURRENT->getSpecularIntensity());
	setUniformFloat("specularPower", Material::CURRENT->getSpecularPower());
	
	setUniformDirectionalLight("directionalLight", **m_activeDirectionalLight);
}

void ForwardDirectional::addDirectionalLight(DirectionalLight *directionalLight)
{
	m_directionalLights.push_back(directionalLight);
}