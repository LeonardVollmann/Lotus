#ifndef LOTUS_ENGINE_H
#define LOTUS_ENGINE_H

#include "../graphics/window.h"

namespace lotus {
    
    class Engine
    {
    private:
        bool m_running;
        double m_frameTime;
        
        graphics::Window m_window;
    public:
        Engine(int fps, int width, int height, const char *title);
        virtual ~Engine();
        
        void start();
        void stop();
    private:
        void update(float delta);
        void render();
    };
    
}

#endif