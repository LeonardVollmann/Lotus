#include "lotus_input.hpp"

bool Input::s_keys[512];
bool Input::s_mouseButtons[64];

bool Input::s_cursorVisible;
bool Input::s_mouseLocked;
vec2 Input::s_cursorPos;
vec2 Input::s_oldCursorPos;
vec2 Input::s_cursorPosDelta;

GLFWwindow *Input::s_window;

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	s_keys[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
}

void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	s_mouseButtons[button] = action == GLFW_PRESS;
}

void Input::update(GLFWwindow *window)
{
	int width, height;
	double xpos, ypos;
	glfwGetWindowSize(window, &width, &height);
	glfwGetCursorPos(window, &xpos, &ypos);
	
	const double xNormalized = (xpos / (double) width - 0.5) * 2.0;
	const double yNormalized = (ypos / (double) height - 0.5) * 2.0;
	
	s_oldCursorPos = s_cursorPos;
	s_cursorPos = vec2(xNormalized, yNormalized);
	s_cursorPosDelta = s_cursorPos - s_oldCursorPos;
	
	if (s_mouseLocked)
	{
		glfwSetCursorPos(window, (float) width / 2.0f, (float) height / 2.0f);
		s_cursorPos = vec2();
	}
}

void Input::setCursorVisible(bool visible)
{
	s_cursorVisible = visible;

	if (s_cursorVisible)
	{
		glfwSetInputMode(s_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		glfwSetInputMode(s_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
}