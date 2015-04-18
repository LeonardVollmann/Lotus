#include "lotus_scenelayer.hpp"
#include "../renderers/lotus_simplerenderer.hpp"

SceneLayer::SceneLayer(float fov, float aspect, float near, float far, Shader *shader) :
	Layer(mat4::perspective(fov, aspect, near, far), new SimpleRenderer(), shader) {}

void SceneLayer::updateProjection(float fov, float aspect, float near, float far)
{
	m_projection = mat4::perspective(fov, aspect, near, far);
}