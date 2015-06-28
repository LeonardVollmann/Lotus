#include "lotus_forwardambient.hpp"

ForwardAmbient &ForwardAmbient::getInstance()
{
	static ForwardAmbient instance;
	return instance;
}

ForwardAmbient::ForwardAmbient() :
	Shader("forward_ambient"),
	m_ambientLight(0.1f, 0.1f, 0.1f)
{
	addVertexShader("forward_shared");
	addFragmentShader(m_fileName);
	compile();
}

void ForwardAmbient::updateUniforms() const
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

	setUniformVec3("ambientLight", m_ambientLight);
}