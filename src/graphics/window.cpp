#include "window.h"

#include <iostream>

namespace lotus { namespace graphics {
    
    void resizeWindow(GLFWwindow *window, int width, int height);

    Window::Window(int width, int height, const char *title) :
        m_width(width),
        m_height(height),
        m_title(title)
    {
        if(!init())
        {
            glfwTerminate();
        }
    }
    
    Window::~Window() {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
    
    bool Window::isClosed()
    {
        return glfwWindowShouldClose(m_window) == 1;
    }
    
    void Window::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void Window::update()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }
    
    bool Window::init()
    {
        if (!glfwInit())
        {
            std::cout << "ERROR: Failed to initialize GLFW" << std::endl;
            return false;
        }
        
        m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
        if (!m_window)
        {
            std::cout << "ERROR: Failed to create window" << std::endl;
            return false;
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwMakeContextCurrent(m_window);
        
        glewExperimental = GL_TRUE;
        GLenum status = glewInit();
        if (status != GLEW_OK) {
            std::cerr << "ERROR: Failed to initialize GLEW: status = " << status << std::endl;
        }
        
        glfwSetWindowSizeCallback(m_window, resizeWindow);
        
        return true;
    }
    
    void resizeWindow(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

} }