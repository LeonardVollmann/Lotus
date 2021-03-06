#include "input.hpp"
#include "../maths/vector.hpp"

namespace lotus
{

bool Input::s_keys[512];
bool Input::s_mouseButtons[64];

bool Input::s_cursorVisible;
bool Input::s_mouseLocked;
maths::vec2f Input::s_cursorPos;
maths::vec2f Input::s_oldCursorPos;
maths::vec2f Input::s_cursorPosDelta;

graphics::Window *Input::s_window;

void Input::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	s_keys[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
}

void Input::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	s_mouseButtons[button] = action == GLFW_PRESS;
}

void Input::update()
{
	float width  = (float)s_window->getWidth();
	float height = (float)s_window->getHeight();

	double xpos, ypos;
	glfwGetCursorPos(s_window->getWindow(), &xpos, &ypos);

	const float xNormalized = -(width / 2.0f - (float)xpos) / width * 2.0f;
	const float yNormalized = -(height / 2.0f - (float)ypos) / height * 2.0f;

	s_oldCursorPos   = s_cursorPos;
	s_cursorPos      = maths::vec2f(xNormalized, yNormalized);
	s_cursorPosDelta = s_cursorPos - s_oldCursorPos;

	if (s_mouseLocked)
	{
		glfwSetCursorPos(s_window->getWindow(), (float)width / 2.0f, (float)height / 2.0f);
		s_cursorPos = maths::vec2f(0.0f);
	}
}

void Input::setCursorVisible(bool visible)
{
	s_cursorVisible = visible;

	if (s_cursorVisible)
	{
		glfwSetInputMode(s_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		glfwSetInputMode(s_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
}
}