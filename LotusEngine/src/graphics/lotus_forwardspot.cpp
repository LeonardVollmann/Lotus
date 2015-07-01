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
	
	setUniformInteger("material_diffuse", 0);
	setUniformInteger("material_normalMap", 1);
	setUniformInteger("material_dispMap", 2);

	mat4 transformation = Transform::CURRENT->getTransformation();
	setUniformMat4("mvp_matrix", Scene::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix() * transformation);
	setUniformMat4("ml_matrix", transformation);
	
	setUniformVec3("camera_pos", Camera::CURRENT->getTransform().getPos());
	
	setUniformSpotLight("spotLight", **m_activeSpotLight);
}

void ForwardSpot::addSpotLight(SpotLight *spotLight)
{
	m_spotLights.push_back(spotLight);
}