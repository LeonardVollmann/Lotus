#include "profiling.hpp"

#include <iostream>

namespace lotus {

	ProfileTimer::ProfileTimer() :
		m_numInvocations(0),
		m_startTime(0.0),
		m_totalTime(0.0) {}

	void ProfileTimer::start()
	{
		m_startTime = Time::getTime();
	}

	void ProfileTimer::stop()
	{
		m_totalTime += (Time::getTime() - m_startTime);
		m_numInvocations++;
	}

	void ProfileTimer::displayAndReset(const std::string &message)
	{
		std::cout << message << (1000.0 * m_totalTime) / (double) m_numInvocations << " ms" << std::endl;

		m_numInvocations = 0;
		m_totalTime = 0.0;
	}

}
