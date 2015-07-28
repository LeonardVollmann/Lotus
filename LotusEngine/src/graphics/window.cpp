#include "window.hpp"
#include "../core/input.hpp"

#include <iostream>

namespace lotus { namespace graphics {

	void callback_resize(GLFWwindow *window, int width, int height);
	void callback_key(GLFWwindow* window, int key, int scancode, int action, int mods);
	void callback_mouse_button(GLFWwindow* window, int button, int action, int mods);

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

	Window::~Window()
	{
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

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
		if (!m_window)
		{
			std::cout << "ERROR: Failed to create window" << std::endl;
			return false;
		}

		glfwSetWindowUserPointer(m_window, this);
		glfwSetWindowSizeCallback(m_window, callback_resize);
		glfwSetKeyCallback(m_window, callback_key);
		glfwSetMouseButtonCallback(m_window, callback_mouse_button);
		glfwMakeContextCurrent(m_window);

		Input::setWindow(this);

		glewExperimental = GL_TRUE;
		GLenum status = glewInit();
		if (status != GLEW_OK)
		{
			std::cerr << "ERROR: Failed to initialize GLEW: status = " << status << std::endl;
		}
		
		std::cout << "ERROR: OpenGL error: " << glGetError() << "." << std::endl;

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_CLAMP);
		// glEnable(GL_CULL_FACE);
		// glCullFace(GL_BACK);

		return true;
	}

	void callback_resize(GLFWwindow *window, int width, int height)
	{
		Window *win = (Window*) glfwGetWindowUserPointer(window);
		win->setWidth(width);
		win->setHeight(height);
	}

	void callback_key(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Input::keyCallback(window, key, scancode, action, mods);
	}

	void callback_mouse_button(GLFWwindow* window, int button, int action, int mods)
	{
		Input::mouseButtonCallback(window, button, action, mods);
	}

} }