#include "engine.h"
#include "time.h"

#include <stdint.h>
#include <iostream>

namespace lotus {
    
    Engine::Engine(int fps, int width, int height, const char *title) :
        m_frameTime(1.0 / (double) fps),
        m_window(width, height, title),
        m_running(false)
    {
        initGL();
    }

    Engine::~Engine()
    {}
    
    void Engine::start()
    {
        if (m_running)
        {
            return;
        }
        
        uint32_t frames = 0;
        uint32_t updates = 0;
        double frameCounterTime = 0.0;
        double time_0 = time::getTime();
        double time_1;
        double unprocessed;
        double delta;
        m_running = true;
        while (m_running)
        {
            if (m_window.isClosed()) {
                stop();
                continue;
            }
            
            time_1 = time::getTime();
            delta = time_1 - time_0;
            time_0 = time_1;
            
            unprocessed += delta;
            frameCounterTime += delta;
            
            while (unprocessed >= m_frameTime) {
                unprocessed -= m_frameTime;
                
                update((float) m_frameTime);
                updates++;
            }
            
            if (frameCounterTime >= 1) {
                std::cout << 1000.0 / frames << " ms (" << frames << " fps, " << updates << " ups)" << std::endl;
                
                frameCounterTime = 0;
                frames = 0;
                updates = 0;
            }
            
            render();
            frames++;
        }
    }
    
    void Engine::stop()
    {
        m_running = false;
    }
    
    void Engine::update(float delta)
    {
        m_game->update(delta);
    }
    
    void Engine::render()
    {
        m_window.clear();
        
        m_game->render();
        
        m_window.update();
    }
    
    void Engine::initGL()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);
        glCullFace(GL_BACK);
        glEnable(GL_DEPTH_CLAMP);
    }
    
}