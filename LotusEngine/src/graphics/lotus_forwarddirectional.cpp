#include "lotus_forwarddirectional.hpp"

ForwardDirectional &ForwardDirectional::getInstance()
{
	static ForwardDirectional instance;
	return instance;
}

ForwardDirectional::ForwardDirectional() :
	Shader("forward_directional")
{
	addVertexShader("forward_shared");
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
	Shader::updateUniforms(transform);

	setUniformInteger("diffuse", 0);
	setUniformInteger("normalMap", 1);
	setUniformInteger("dispMap", 2);
	
	mat4 transformation = transform.getTransformation();
	setUniformMat4("mvp_matrix", Scene::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix() * transformation);
	setUniformMat4("ml_matrix", transformation);
	
	setUniformVec3("cameraPos", Camera::CURRENT->getTransform().getPos());
	
	setUniformVec4("baseColor", Material::CURRENT->getVec4("color"));
	setUniformFloat("specularIntensity", Material::CURRENT->getFloat("specularIntensity"));
	setUniformFloat("specularPower", Material::CURRENT->getFloat("specularPower"));

	setUniformFloat("dispMapScale", Material::CURRENT->getFloat("dispMapScale"));
	setUniformFloat("dispMapBias", Material::CURRENT->getFloat("dispMapBias"));
	
	setUniformDirectionalLight("directionalLight", **m_activeDirectionalLight);
}

void ForwardDirectional::addDirectionalLight(DirectionalLight *directionalLight)
{
	m_directionalLights.push_back(directionalLight);
}