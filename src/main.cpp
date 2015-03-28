#include <iostream>

#include "maths/maths.hpp"
#include "graphics/window.hpp"

int main()
{
	using namespace lotus;
	using namespace lotus::maths;
	using namespace lotus::graphics;

	Window window(800, 600, "Lotus");

	while (!window.isClosed())
	{
		window.clear();

		window.update();
	}

	return 0;
}