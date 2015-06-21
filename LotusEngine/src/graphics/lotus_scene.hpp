#ifndef LOTUS_SCENE_HPP_INCLUDED
#define LOTUS_SCENE_HPP_INCLUDED

#include "lotus_entity.hpp"
#include "lotus_mat4.hpp"

#include <vector>

class IRenderer;

class Scene
{
public:
	static const Scene *CURRENT;
protected:
	mat4					m_projection;
	IRenderer				*m_renderer;
	std::vector<Entity*>	m_entities;
public:
	Scene(const mat4 &m_projection, IRenderer *renderer);
	virtual ~Scene();

	void update(double delta);
	void render() const;
	void bind() const;
	void add(Entity *entity);

	inline const mat4 &getProjection() const { return m_projection; }
	inline void setProjection(const mat4 &projection) { m_projection = projection; }
};

#endif