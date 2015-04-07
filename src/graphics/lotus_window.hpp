#ifndef LOTUS_WINDOW_HPP_INCLUDED
#define LOTUS_WINDOW_HPP_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace lotus { namespace graphics {

	class Window
	{
	private:
		GLFWwindow 	*m_window;
		int 		m_width;
		int 		m_height;
		const char 	*m_title;
	public:
		Window(int width, int height, const char *title);
		virtual ~Window();

		bool isClosed();

		void clear();
		void update();

		inline int getWidth() 		const { return m_width; }
		inline int getHeight() 		const { return m_height; }
		inline float getAspect() 	const { return (float) m_width / (float) m_height; }

		inline void setWidth(int width)		{ m_width = width; }
		inline void setHeight(int height)	{ m_height = height; }
		private:
		bool init();
	};

} }

#endif