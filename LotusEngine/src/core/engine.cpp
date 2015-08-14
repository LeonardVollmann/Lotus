#include "engine.hpp"
#include "igame.hpp"
#include "time.hpp"
#include "input.hpp"
#include "../graphics/shaders/shaderfactory.hpp"

#include <string>
#include <iostream>

namespace lotus {

	Engine::Engine(double fps, int width, int height, const char *title) :
		m_window(width, height, title),
		m_fps(fps),
		m_running(false)
	{
		initSubsystems();
	}

	void Engine::setGame(IGame *game)
	{
		m_game = game;
		m_game->setEngine(this);
		m_game->init();
	}

	void Engine::initSubsystems() const
	{
	}

	void Engine::start()
	{
		if (m_game == nullptr)
		{
			std::cout << "ERROR: Engine::start() called before Engine::setGame(IGame *game)." << std::endl;
			return;
		}

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

	void Engine::update(float delta)
	{
		Input::update();
		m_game->update(delta);
	}

	void Engine::render()
	{
		m_window.clear();

		m_game->render();

		m_window.update();
	}

	void Engine::run()
	{
		const double freq = 1.0 / (double) m_fps;

		double time_0 = Time::getTime();
		double time_1 = 0.0;
		double delta;
		double unprocessed = 0.0;
		double accumulatedDelta = 0.0;
		unsigned int frames = 0;
		unsigned int updates = 0;
		while (m_running)
		{
			if (m_window.isClosed())
			{
				stop();
			}

			time_1 = Time::getTime();
			delta = time_1 - time_0;
			time_0 = time_1;

			unprocessed += delta;
			accumulatedDelta += delta;

			while (unprocessed >= freq)
			{
				unprocessed -= freq;
				update(freq);
				updates++;
			}

			render();
			frames++;

			if (accumulatedDelta >= 1.0)
			{
				m_game->tick();
				std::cout << delta * 1000 << " ms, " << updates << " updates, " << frames << " frames." << std::endl;
				updates = 0;
				frames = 0;
				accumulatedDelta = 0;
			}
		}
		
		shutdownSubsystems();
	}

	void Engine::shutdownSubsystems() const
	{
		m_game->shutdown();
		graphics::ShaderFactory::shutdown();
	}

}
