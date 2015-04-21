#include "lotus_forwardpoint.hpp"

ForwardPoint &ForwardPoint::getInstance()
{
	static ForwardPoint instance;
	return instance;
}

ForwardPoint::ForwardPoint() :
Shader("forwardpoint")
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
	
	addUniform("pointLight.base.color");
	addUniform("pointLight.base.intensity");
	addUniform("pointLight.atten.constant");
	addUniform("pointLight.atten.linear");
	addUniform("pointLight.atten.exponent");
	addUniform("pointLight.pos");
	addUniform("pointLight.range");
}

ForwardPoint::~ForwardPoint()
{
	for (auto it = m_pointLights.begin(); it < m_pointLights.end(); it++)
	{
		delete *it;
	}
}


void ForwardPoint::updateUniforms(const Transform &transform) const
{
	setUniformMat4("pr_matrix", Layer::CURRENT->getProjection());
	setUniformMat4("vw_matrix", Camera::CURRENT->getViewMatrix());
	setUniformMat4("ml_matrix", transform.getTransformation());
	
	setUniformVec3("cameraPos", Camera::CURRENT->getTransform().getPos());
	
	setUniformVec4("baseColor", Material::CURRENT->getColor());
	setUniformFloat("specularIntensity", Material::CURRENT->getSpecularIntensity());
	setUniformFloat("specularPower", Material::CURRENT->getSpecularPower());
	
	setUniformPointLight("pointLight", **m_activePointLight);
}

void ForwardPoint::addPointLight(PointLight *pointLight)
{
	m_pointLights.push_back(pointLight);
}