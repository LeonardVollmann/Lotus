#include "lotus_input.hpp"

namespace lotus {
	
	bool Input::s_keys[512];
	bool Input::s_mouseButtons[64];
	
	bool Input::s_cursorVisible;
	bool Input::s_mouseLocked;
	maths::vec2 Input::s_cursorPos;
	maths::vec2 Input::s_oldCursorPos;
	maths::vec2 Input::s_cursorPosDelta;

	GLFWwindow *Input::s_window;

	void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		s_keys[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
	}

	void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		s_mouseButtons[button] = action == GLFW_PRESS;
	}

	void Input::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
	{
		s_oldCursorPos = s_cursorPos;
		s_cursorPos = maths::vec2((float) xpos, (float) ypos);
		s_cursorPosDelta = s_cursorPos;

		if (!s_mouseLocked)
		{
			s_cursorPosDelta -= s_oldCursorPos;
			return;
		}

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glfwSetCursorPos(window, (float) width / 2.0f, (float) height / 2.0f);
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

}