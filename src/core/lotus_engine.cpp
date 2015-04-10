#include "lotus_engine.hpp"
#include "lotus_igame.hpp"
#include "lotus_time.hpp"

#include <string>
#include <iostream>

Engine::Engine(IGame *game, double fps, int width, int height, const char *title) :
	m_game(game),
	m_window(width, height, title),
	m_fps(fps),
	m_running(false)
{

}

void Engine::start()
{
	if (m_running)
	{
		return;
	}
	else
	{
		m_running = true;
		run();
	}
}

void Engine::stop()
{
	m_running = false;
}

void Engine::update(double delta)
{
	m_game->update(delta);
}

void Engine::render()
{

}

void Engine::run()
{
	const double freq = 1.0 / (double) m_fps;

	double time_0 = Time::getTime();
	double time_1 = 0;
	double delta = 0;
	double unprocessed = 0;
	double accumulatedDelta;
	unsigned int frames;
	unsigned int updates;
	while (m_running)
	{
		if (m_window.isClosed())
		{
			stop();
		}

		time_1 = Time::getTime();
		delta = time_1 - time_0;
		unprocessed += delta;
		accumulatedDelta += delta;

		while (unprocessed >= freq)
		{
			unprocessed--;
			update(delta);
			updates++;
		}

		render();
		frames++;

		if (accumulatedDelta >= 1.0)
		{
			std::cout << updates << " updates, " << frames << " frames." << std::endl;
			updates = 0;
			frames = 0;
			accumulatedDelta = 0;
		}

		time_0 = time_1;
	}
}