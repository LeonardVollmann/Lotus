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


void ForwardPoint::updateUniforms(const Transform &transform) const
{
	Shader::updateUniforms(transform);
	
	setUniformInteger("diffuse", 0);
	setUniformInteger("normalMap", 1);
	setUniformInteger("dispMap", 2);

	mat4 transformation = transform.getTransformation();
	setUniformMat4("mvp_matrix", Layer::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix() * transformation);
	setUniformMat4("ml_matrix", transformation);
	
	setUniformVec3("cameraPos", Camera::CURRENT->getTransform().getPos());
	
	setUniformVec4("baseColor", Material::CURRENT->getVec4("color"));
	setUniformFloat("specularIntensity", Material::CURRENT->getFloat("specularIntensity"));
	setUniformFloat("specularPower", Material::CURRENT->getFloat("specularPower"));
	
	setUniformFloat("dispMapScale", Material::CURRENT->getFloat("dispMapScale"));
	setUniformFloat("dispMapBias", Material::CURRENT->getFloat("dispMapBias"));

	setUniformPointLight("pointLight", **m_activePointLight);
}

void ForwardPoint::addPointLight(PointLight *pointLight)
{
	m_pointLights.push_back(pointLight);
}