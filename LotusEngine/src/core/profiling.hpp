#ifndef LOTUS_PROFILING_HPP_INCLUDED
#define LOTUS_PROFILING_HPP_INCLUDED

#include "time.hpp"

#include <string>

namespace lotus {

	class ProfileTimer
	{
	public:
		ProfileTimer();

		void start();
		void stop();
		void displayAndReset(const std::string &message);
	private:
		unsigned int	m_numInvocations;
		double			m_startTime;
		double			m_totalTime;
	};

}

#endif
