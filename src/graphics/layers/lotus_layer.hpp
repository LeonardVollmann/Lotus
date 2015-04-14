#ifndef LOTUS_LAYER_HPP_INCLUDED
#define LOTUS_LAYER_HPP_INCLUDED

#include "../renderers/lotus_irenderer.hpp"
#include "../shaders/lotus_shader.hpp"
#include "../../core/lotus_entity.hpp"
#include "../../maths/lotus_mat4.hpp"

#include <vector>

class Layer : public Entity
{
protected:
	mat4 		m_projection;
	IRenderer 	*m_renderer;
	Shader 		*m_shader;
public:
	virtual ~Layer();

	void render();

	inline const mat4 &getProjection() const { return m_projection; }
	inline void setProjection(const mat4 &projection) { m_projection = projection; }
protected:
	Layer(const mat4 &m_projection, IRenderer *renderer, Shader *shader);
};

#endif