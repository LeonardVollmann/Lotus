#ifndef LOTUS_ENGINE_HPP_INCLUDED
#define LOTUS_ENGINE_HPP_INCLUDED

#include "profiling.hpp"
#include "../graphics/window.hpp"

#include <vector>

namespace lotus {

	class IGame;

	class Engine
	{
	public:
		Engine(double fps, int width, int height, const char *title);

		void setGame(IGame *game);
		void initSubsystems() const;
		void start();
		void stop();
		void update(float delta);
		void render();
		void shutdownSubsystems() const;
	private:
		void run();
	private:
		graphics::Window m_window;
		IGame			*m_game;
		
		double			m_fps;
		bool			m_running;

		ProfileTimer	m_updateTimer;
		ProfileTimer	m_renderTimer;
		ProfileTimer	m_loopTimer;
	};

}

#endif
