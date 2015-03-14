#ifndef LOTUS_WINDOW_H
#define LOTUS_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace lotus { namespace graphics {
   
    class Window
    {
    private:
        GLFWwindow *m_window;
        int m_width, m_height;
        const char *m_title;
    public:
        Window(int width, int height, const char *title);
        virtual ~Window();
        
        bool isClosed();
        
        void clear();
        void update();
    private:
        bool init();
    };
    
} }

#endif