#include "profiling.hpp"

#include <algorithm>

namespace lotus
{

std::string ProfilingInfo::getInfoMessage(ProfilingVerbosity verbosity)
{
	std::string message = name + ": ";
	if (verbosity == ProfilingVerbosity::LOW)
	{
		message += std::to_string(totalTime / (double)numInvocations * 1000.0);
	}
	else if (verbosity == ProfilingVerbosity::HIGH)
	{
		message += "\n\tTimer Invocations:   " + std::to_string(numInvocations);
		message += "\n\tTotal Time:          " + std::to_string(totalTime);
		message += "\n\tTime Per Invocation: " +
		           std::to_string(totalTime / (double)numInvocations * 1000.0);
	}
	else
	{
		message += "ERROR: Invalid Verbosity Level";
	}
	return message;
}

std::vector<ProfileTimer *> ProfileTimer::s_profileTimers;

std::string ProfileTimer::getInfoMessage(ProfilingVerbosity verbosity)
{
	std::string message = "Profiling results:\n";
	for (auto it = s_profileTimers.begin(); it < s_profileTimers.end(); it++)
	{
		message += (*it)->reset().getInfoMessage(verbosity);
		message += "\n";
	}
	message += "\n";
	return message;
}

ProfileTimer::ProfileTimer(const std::string &name)
: m_name(name)
, m_numInvocations(0)
, m_startTime(0.0)
, m_totalTime(0.0)
{
	s_profileTimers.push_back(this);
}

ProfileTimer::~ProfileTimer()
{
	s_profileTimers.erase(std::find(s_profileTimers.begin(), s_profileTimers.end(), this));
}

void ProfileTimer::start()
{
	m_startTime = Time::getTime();
}

void ProfileTimer::stop()
{
	m_totalTime += (Time::getTime() - m_startTime);
	m_numInvocations++;
}

ProfilingInfo ProfileTimer::reset()
{
	ProfilingInfo info;
	info.name           = m_name;
	info.numInvocations = m_numInvocations;
	info.totalTime      = m_totalTime;

	m_numInvocations = 0;
	m_totalTime      = 0.0;

	return info;
}

} // namespace lotus