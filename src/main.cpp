#include "graphics/window.h"

#include <iostream>

int main()
{
    lotus::graphics::Window window(600, 400, "Lotus Engine!");
    
    while (!window.closed())
    {
        window.clear();
        
        glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(-0.5f,  0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f( 0.5f, -0.5f);
        glEnd();
        
        window.update();
    }
}