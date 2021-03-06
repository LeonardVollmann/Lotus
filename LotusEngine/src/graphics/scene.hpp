#pragma once

#include "../core/entity.hpp"
#include "../maths/types.hpp"

#include <vector>
#include <memory>

namespace lotus
{
namespace graphics
{

class IRenderer;

class Scene
{
public:
	static const Scene *CURRENT;

protected:
	maths::mat4f m_projection;
	IRenderer *m_renderer;
	std::vector<std::unique_ptr<Entity>> m_entities;

public:
	Scene(const maths::mat4f &m_projection, IRenderer *renderer);
	virtual ~Scene();

	template <typename ENTITY_T, typename... ARGS>
	void add(ARGS &&... args);

	void update(double delta);
	void render() const;
	void bind() const;
	void add(Entity *entity);

	inline const maths::mat4f &getProjection() const { return m_projection; }
	inline void setProjection(const maths::mat4f &projection) { m_projection = projection; }
};

} // namespace graphics
} // namespace lotus