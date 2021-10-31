#include "jlTimer.h"

namespace jlUtilitiesSDK {

		jlTimer::jlTimer()	{
				reset();
		}

		void 
		jlTimer::reset()	{
				m_startTime = m_highResClock.now();
		}

		uint64 
		jlTimer::getMilliseconds() const	{
				auto newTime = m_highResClock.now();
				std::chrono::duration<double> dur = newTime - m_startTime;
				return duration_cast<std::chrono::milliseconds>(dur).count();
		}
		
		uint64 
		jlTimer::getMicroseconds() const {
				auto newTime = m_highResClock.now();
				std::chrono::duration<double> dur = newTime - m_startTime;
				return duration_cast<std::chrono::microseconds>(dur).count();
		}
		
		float 
		jlTimer::getSeconds() const	{
				auto newTime = m_highResClock.now();
				std::chrono::duration<double> dur = newTime - m_startTime;
				return (float)duration_cast<std::chrono::microseconds>(dur).count() / 1000000.0f;
		}

		uint64 
		jlTimer::getStartMilliseconds() const	{
				std::chrono::nanoseconds startTimeNs = m_startTime.time_since_epoch();
				return duration_cast<std::chrono::milliseconds>(startTimeNs).count();
		}
}