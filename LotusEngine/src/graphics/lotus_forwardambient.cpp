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
	
	mat4 transformation = Transform::CURRENT->getTransformation();
	setUniformMat4("mvp_matrix", Scene::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix() * transformation);
	setUniformMat4("ml_matrix", transformation);
	
	setUniformVec3("camera_pos", Camera::CURRENT->getTransform().getPos());

	setUniformVec3("ambientLight", m_ambientLight);
}