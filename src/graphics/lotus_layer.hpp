#ifndef LOTUS_LAYER_HPP_INCLUDED
#define LOTUS_LAYER_HPP_INCLUDED

#include "../core/lotus_entity.hpp"
#include "../maths/lotus_mat4.hpp"

#include <vector>

class IRenderer3D;

class Layer : public Entity
{
public:
	static const Layer *CURRENT;
protected:
	mat4			m_projection;
	IRenderer3D 	*m_renderer;
public:
	Layer(const mat4 &m_projection, IRenderer3D *renderer);
	virtual ~Layer();

	virtual void render(IRenderer3D *renderer = nullptr) const override;
	void bind() const;

	inline const mat4 &getProjection() const { return m_projection; }
	inline void setProjection(const mat4 &projection) { m_projection = projection; }
};

#endif