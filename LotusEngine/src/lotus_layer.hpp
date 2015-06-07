#ifndef LOTUS_LAYER_HPP_INCLUDED
#define LOTUS_LAYER_HPP_INCLUDED

#include "lotus_entity.hpp"
#include "lotus_mat4.hpp"

#include <vector>

class IRenderer;

class Layer : public Entity
{
public:
	static const Layer *CURRENT;
protected:
	mat4			m_projection;
	IRenderer 	*m_renderer;
public:
	Layer(const mat4 &m_projection, IRenderer *renderer);
	virtual ~Layer();

	virtual void render(IRenderer *renderer = nullptr) const override;
	void bind() const;

	inline const mat4 &getProjection() const { return m_projection; }
	inline void setProjection(const mat4 &projection) { m_projection = projection; }
};

#endif