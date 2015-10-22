#ifndef LOTUS_INPUT_HPP_INCLUDED
#define LOTUS_INPUT_HPP_INCLUDED

#include "../core/maths.hpp"
#include "../graphics/window.hpp"

#include <GLFW/glfw3.h>

namespace lotus {

	class Input
	{
	public:
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

		static void update();
		
		inline static bool getKey(int key)							{ return s_keys[key]; }
		inline static bool getMouseButton(int button)				{ return s_mouseButtons[button]; }
		inline static const maths::Vector2f &getCursorPos()			{ return s_cursorPos; }
		inline static const maths::Vector2f &getOldCursorPos()		{ return s_oldCursorPos; }
		inline static const maths::Vector2f &getCursorPosDelta() 	{ return s_cursorPosDelta; }
		inline static bool isCursorVisible()						{ return s_cursorVisible; }
		inline static bool isMouseLocked()					{ return s_mouseLocked; }

		static void setCursorVisible(bool visible);
		inline static void setMouseLocked(bool mouseLocked) 	{ s_mouseLocked = mouseLocked; }
		inline static void setWindow(graphics::Window *window)	{ s_window = window; }
	private:
		static bool				s_keys[512];
		static bool				s_mouseButtons[64];
		static bool				s_cursorVisible;
		static bool				s_mouseLocked;
		static maths::Vector2f 	s_cursorPos;
		static maths::Vector2f 	s_oldCursorPos;
		static maths::Vector2f 	s_cursorPosDelta;
		
		static graphics::Window *s_window;
	};

}

#endif