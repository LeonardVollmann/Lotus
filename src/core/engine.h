#ifndef LOTUS_ENGINE_H
#define LOTUS_ENGINE_H

#include "game.h"
#include "../graphics/window.h"

namespace lotus {
    
    class Engine
    {
    private:
        bool m_running;
        double m_frameTime;
        
        graphics::Window m_window;
        Game *m_game;
    public:
        Engine(int fps, int width, int height, const char *title);
        virtual ~Engine();
        
        void start();
        void stop();
        
        inline void setGame(Game *game) { m_game = game; }
    private:
        void update(float delta);
        void render();
        void initGL();
    };
    
}

#endif