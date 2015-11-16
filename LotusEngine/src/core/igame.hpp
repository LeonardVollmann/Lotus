#ifndef LOTUS_I_GAME_HPP_INCLUDED
#define LOTUS_I_GAME_HPP_INCLUDED

#include "engine.hpp"
#include "entity.hpp"
#include "../graphics/scene.hpp"
#include "../graphics/camera.hpp"

#include <vector>

namespace lotus {

	class IGame
	{
	public:
		IGame() :
			m_camera(new graphics::Camera) {}

		virtual void init() = 0;
		virtual void shutdown() = 0;
		virtual void tick() = 0;

		virtual void update(double delta)
		{
			m_camera->update(delta);

			for (auto it = m_scenes.begin(); it < m_scenes.end(); it++)
			{
				(*it)->update(delta);
			}
		}

		virtual void render()
		{
			for (auto it = m_scenes.begin(); it < m_scenes.end(); it++)
			{
				(*it)->render();
			}
		}

		inline void setEngine(Engine *engine)	{ m_engine = engine; }
		inline void addScene(graphics::Scene *scene)		{ m_scenes.push_back(scene); }
		inline void setCamera(graphics::Camera *camera)	{ m_camera = camera; }
	protected:
		Engine 							*m_engine;
		std::vector<graphics::Scene*> 	m_scenes;
		graphics::Camera				*m_camera;
	private:
	};

}

#endif
