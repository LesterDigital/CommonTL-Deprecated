#pragma once

#include <chrono>
#include <iostream>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

namespace Time
{
	__int64 unixTime_sec();
	__int64 unixTime_ms();
	__int64 unixTime_ns();

	class TimeBomb
	{
	private:
		enum Units
		{
			Sec, Ms, Ns
		};

		__int8 UnitMode;
		__int64 Start = 0;
		__int64 End = 0;

		bool ActivatedFlag = false;
	private:
		__int64 unixTime();
		__int8 SetMode(__int8 code);
	public:
		TimeBomb(__int8 code = Ms);

		void Activate();
		__int64 Explode(const char* title);
	};

	class ScopedTimer
	{
	public:
		ScopedTimer()
		{
			m_Start = unixTime_ms();
		}
		~ScopedTimer()
		{
			std::cout << unixTime_ms() - m_Start << " ms" << std::endl;
		}
	private:
		int64_t m_Start;
	};
}
