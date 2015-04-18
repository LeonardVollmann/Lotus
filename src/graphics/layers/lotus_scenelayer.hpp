#ifndef LOTUS_SCENE_LAYER_HPP_INCLUDED
#define LOTUS_SCENE_LAYER_HPP_INCLUDED

#include "lotus_layer.hpp"
#include "../shaders/lotus_shader.hpp"

class SceneLayer : public Layer
{
public:
	SceneLayer(float fov, float aspect, float near, float far, Shader *shader);

	void updateProjection(float fov, float aspect, float near, float far);
};

#endif