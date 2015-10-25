#ifndef LOTUS_WINDOW_HPP_INCLUDED
#define LOTUS_WINDOW_HPP_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../core/profiling.hpp"

namespace lotus { namespace graphics {

	class Window
	{
	public:
		static const Window *CURRENT;

		Window(int width, int height, const char *title);
		virtual ~Window();

		bool isClosed();

		void clear() const;
		void update();
		void bindAsRenderTarget() const;
		void bind() const;

		inline GLFWwindow *getWindow()	const { return m_window; }
		inline int getWidth()			const { return m_width; }
		inline int getHeight()			const { return m_height; }
		inline float getAspect()		const { return (float) m_width / (float) m_height; }

		inline void setWidth(int width)		{ m_width = width; }
		inline void setHeight(int height)	{ m_height = height; }
	private:
		bool init();
	private:
		GLFWwindow		*m_window;
		int				m_width;
		int				m_height;
		const char		*m_title;

		ProfileTimer	m_updateTimer;
	};

} }

#endif
