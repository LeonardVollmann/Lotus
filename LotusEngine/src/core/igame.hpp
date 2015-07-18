#ifndef LOTUS_I_GAME_HPP_INCLUDED
#define LOTUS_I_GAME_HPP_INCLUDED

#include "engine.hpp"
#include "../graphics/camera.hpp"

#include <memory>

namespace lotus {

	class IGame
	{
	protected:
		Engine 					*m_engine;
		std::unique_ptr<Node> 	m_root;
	public:
		IGame() :
			m_root(new Node()) {}

		virtual void init() = 0;
		virtual void tick() = 0;
		virtual void update(double delta) = 0;
		virtual void render() = 0;

		inline void setEngine(Engine *engine)	{ m_engine = engine; }
	};

}

#endif