#ifndef LOTUS_TIME_HPP_INCLUDED
#define LOTUS_TIME_HPP_INCLUDED

#include <chrono>

namespace lotus {

	namespace Time
	{
		const std::chrono::time_point<std::chrono::high_resolution_clock> m_epoch = std::chrono::high_resolution_clock::now();
		
		inline double getTime()
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_epoch).count() / 1000000000.0;
		}
	};

}

#endif
