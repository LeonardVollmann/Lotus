#ifndef LOTUS_SCENE_HPP_INCLUDED
#define LOTUS_SCENE_HPP_INCLUDED

#include "../core/entity.hpp"
#include "../core/maths.hpp"

#include <vector>
#include <memory>

namespace lotus { namespace graphics {

	class IRenderer;

	class Scene
	{
	public:
		Scene(const maths::Matrix4f &m_projection, IRenderer *renderer);
		virtual ~Scene();

		template <typename ENTITY_T, typename... ARGS>
		void add(ARGS&&... args);

		void update(double delta);
		void render() const;
		void bind() const;
		void add(Entity *entity);

		inline const maths::Matrix4f &getProjection() const { return m_projection; }
		inline void setProjection(const maths::Matrix4f &projection) { m_projection = projection; }
	public:
		static const Scene *CURRENT;
	protected:
		maths::Matrix4f							m_projection;
		IRenderer								*m_renderer;
		std::vector<std::unique_ptr<Entity>>	m_entities;
	};

} }

#endif
