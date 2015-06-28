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


void ForwardSpot::updateUniforms() const
{
	Shader::updateUniforms();
	
	setUniformInteger("diffuse", 0);
	setUniformInteger("normalMap", 1);
	setUniformInteger("dispMap", 2);

	mat4 transformation = Transform::CURRENT->getTransformation();
	setUniformMat4("mvp_matrix", Scene::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix() * transformation);
	setUniformMat4("ml_matrix", transformation);
	
	setUniformVec3("cameraPos", Camera::CURRENT->getTransform().getPos());
	
	setUniformVec4("baseColor", *Material::CURRENT->getVec4("color"));
	setUniformFloat("specularIntensity", *Material::CURRENT->getFloat("specularIntensity"));
	setUniformFloat("specularPower", *Material::CURRENT->getFloat("specularPower"));

	setUniformFloat("dispMapScale", *Material::CURRENT->getFloat("dispMapScale"));
	setUniformFloat("dispMapBias", *Material::CURRENT->getFloat("dispMapBias"));
	
	setUniformSpotLight("spotLight", **m_activeSpotLight);
}

void ForwardSpot::addSpotLight(SpotLight *spotLight)
{
	m_spotLights.push_back(spotLight);
}