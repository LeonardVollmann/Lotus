#ifndef LOTUS_I_GAME_HPP_INCLUDED
#define LOTUS_I_GAME_HPP_INCLUDED

#include "lotus_engine.hpp"
#include "lotus_entity.hpp"
#include "lotus_scene.hpp"
#include "lotus_camera.hpp"

#include <vector>

class IGame
{
protected:
	Engine 				*m_engine;
	std::vector<Scene*> m_scenes;
	Camera				*m_camera;
public:
	IGame() :
		m_camera(new Camera) {}
	
	virtual void init() = 0;
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
	inline void addScene(Scene *scene)		{ m_scenes.push_back(scene); }
	inline void setCamera(Camera *camera)	{ m_camera = camera; }
};

#endif