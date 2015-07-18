#ifndef LOTUS_ENGINE_HPP_INCLUDED
#define LOTUS_ENGINE_HPP_INCLUDED

#include "../graphics/window.hpp"

namespace lotus {

	class IGame;

	class Engine
	{
	private:
		graphics::Window 	m_window;
		IGame 				*m_game;

		double 	m_fps;
		bool 	m_running;
	public:
		Engine(double fps, int width, int height, const char *title);

		void setGame(IGame *game);
		void start();
		void stop();
		void update(float delta);
		void render();
	private:
		void run();
		void cleanUp();
	};

}

#endif