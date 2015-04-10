#ifndef LOTUS_I_GAME_HPP_INCLUDED
#define LOTUS_I_GAME_HPP_INCLUDED

#include "lotus_engine.hpp"
#include "lotus_entity.hpp"

class IGame
{
protected:
	Engine *m_engine;
	Entity *m_root;
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
	virtual void update(double delta) = 0;

	inline Entity *getRoot() const { return m_root; }

	void setEngine(Engine *engine) { m_engine = engine; }
};

#endif