#ifndef LOTUS_ENGINE_HPP_INCLUDED
#define LOTUS_ENGINE_HPP_INCLUDED

#include "../graphics/lotus_window.hpp"

class IGame;

class Engine
{
private:
	Window 	m_window;
	IGame 	*m_game;

	double 	m_fps;
	bool 	m_running;
public:
	Engine(double fps, int width, int height, const char *title);

	void setGame(IGame *game);
	void start();
	void stop();
	void update(double delta);
	void render();
private:
	void run();
};

#endif