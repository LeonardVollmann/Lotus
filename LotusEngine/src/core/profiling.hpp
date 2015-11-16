#ifndef LOTUS_PROFILING_HPP_INCLUDED
#define LOTUS_PROFILING_HPP_INCLUDED

#include "time.hpp"

#include <string>
#include <vector>

namespace lotus {

	enum class ProfilingVerbosity
	{
		LOW,
		HIGH
	};

	struct ProfilingInfo
	{
		std::string getInfoMessage(ProfilingVerbosity verbosity);

		std::string		name;
		unsigned int	numInvocations;
		double			totalTime;
	};

	class ProfileTimer
	{
	public:
		static std::string getInfoMessage(ProfilingVerbosity verbosity);

		ProfileTimer(const std::string &name);
		virtual ~ProfileTimer();

		void start();
		void stop();
		ProfilingInfo reset();
	protected:
	private:
		static std::vector<ProfileTimer*> s_profileTimers;

		std::string		m_name;
		unsigned int	m_numInvocations;
		double			m_startTime;
		double			m_totalTime;
	};

}

#endif
