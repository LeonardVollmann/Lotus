#ifndef LOTUS_ENGINE_HPP_INCLUDED
#define LOTUS_ENGINE_HPP_INCLUDED

#include "../graphics/lotus_window.hpp"

class IGame;

class Engine
{
private:
	IGame 	*m_game;
	Window 	m_window;

	double 	m_fps;
	bool 	m_running;
public:
	Engine(IGame *game, double fps, int width, int height, const char *title);
	~Engine();

	void start();
	void stop();
	void update(double delta);
	void render();
private:
	void run();
};

#endif