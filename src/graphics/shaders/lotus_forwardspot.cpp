#include "lotus_forwardspot.hpp"

ForwardSpot &ForwardSpot::getInstance()
{
	static ForwardSpot instance;
	return instance;
}

ForwardSpot::ForwardSpot() :
	Shader("forward/spot")
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
	
	addUniform("spotLight.pointLight.base.color");
	addUniform("spotLight.pointLight.base.intensity");
	addUniform("spotLight.pointLight.atten.constant");
	addUniform("spotLight.pointLight.atten.linear");
	addUniform("spotLight.pointLight.atten.exponent");
	addUniform("spotLight.pointLight.pos");
	addUniform("spotLight.pointLight.range");
	addUniform("spotLight.direction");
	addUniform("spotLight.cutoff");
}

ForwardSpot::~ForwardSpot()
{
	for (auto it = m_spotLights.begin(); it < m_spotLights.end(); it++)
	{
		delete *it;
	}
}


void ForwardSpot::updateUniforms(const Transform &transform) const
{
	mat4 transformation = transform.getTransformation();
	setUniformMat4("mvp_matrix", Layer::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix() * transformation);
	setUniformMat4("ml_matrix", transformation);
	
	setUniformVec3("cameraPos", Camera::CURRENT->getTransform().getPos());
	
	setUniformVec4("baseColor", Material::CURRENT->getColor());
	setUniformFloat("specularIntensity", Material::CURRENT->getSpecularIntensity());
	setUniformFloat("specularPower", Material::CURRENT->getSpecularPower());
	
	setUniformSpotLight("spotLight", **m_activeSpotLight);
}

void ForwardSpot::addSpotLight(SpotLight *spotLight)
{
	m_spotLights.push_back(spotLight);
}