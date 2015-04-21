#include "lotus_forwardpoint.hpp"

ForwardPoint &ForwardPoint::getInstance()
{
	static ForwardPoint instance;
	return instance;
}

ForwardPoint::ForwardPoint() :
Shader("forward/point")
{
	addVertexShader("forward/shared");
	addFragmentShader(m_fileName);
	compile();
	
	addUniform("mvp_matrix");
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
	mat4 transformation = transform.getTransformation();
	setUniformMat4("mvp_matrix", Layer::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix() * transformation);
	setUniformMat4("ml_matrix", transformation);
	
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