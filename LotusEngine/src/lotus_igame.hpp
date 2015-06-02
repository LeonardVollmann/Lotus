#ifndef LOTUS_I_GAME_HPP_INCLUDED
#define LOTUS_I_GAME_HPP_INCLUDED

#include "lotus_engine.hpp"
#include "lotus_entity.hpp"
#include "lotus_layer.hpp"

#include <vector>

class IGame
{
protected:
	Engine 				*m_engine;
	Entity 				*m_root;
	std::vector<Layer*> m_layers;
public:
	IGame()
	{
		m_root = new Entity(Transform());
	}

	virtual ~IGame()
	{
		delete m_root;
	}

	virtual void init() = 0;
	virtual void tick() = 0;
	virtual void update(double delta) = 0;
	
	virtual void render()
	{
		for (auto it = m_layers.begin(); it < m_layers.end(); it++)
		{
			(*it)->render();
		}
	}

	inline Entity *getRoot() const { return m_root; }

	inline void setEngine(Engine *engine) 	{ m_engine = engine; }
	inline void add(Entity *entity)	 		{ m_root->addChild(entity); }
	inline void addLayer(Layer *layer)
	{
		add(layer);
		m_layers.push_back(layer);
	}
};

#endif