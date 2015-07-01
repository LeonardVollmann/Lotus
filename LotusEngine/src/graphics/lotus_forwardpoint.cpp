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
	
	setUniformInteger("material_diffuse", 0);
	setUniformInteger("material_normalMap", 1);
	setUniformInteger("material_dispMap", 2);

	mat4 transformation = Transform::CURRENT->getTransformation();
	setUniformMat4("mvp_matrix", Scene::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix() * transformation);
	setUniformMat4("ml_matrix", transformation);
	
	setUniformVec3("camera_pos", Camera::CURRENT->getTransform().getPos());

	setUniformPointLight("pointLight", **m_activePointLight);
}

void ForwardPoint::addPointLight(PointLight *pointLight)
{
	m_pointLights.push_back(pointLight);
}