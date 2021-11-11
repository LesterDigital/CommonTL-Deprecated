#include "TimeLib.h"

__int64 Time::unixTime_sec()
{
	return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}
__int64 Time::unixTime_ms()
{
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
__int64 Time::unixTime_ns()
{
	return duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
}

__int64 Time::TimeBomb::unixTime()
{
	if (UnitMode == Sec)
		return unixTime_sec();
	else if (UnitMode == Ms)
		return unixTime_ms();
	else
		return unixTime_ns();
}

Time::TimeBomb::TimeBomb(__int8 mode)
	:UnitMode(SetMode(mode)) {}

__int8 Time::TimeBomb::SetMode(__int8 mode) {
	if (mode <= Sec)
		UnitMode = Sec;
	else if (mode >= Ns)
		UnitMode = Ns;
	else
		UnitMode = mode;

	return UnitMode;
}

void Time::TimeBomb::Activate()
{
	Start = unixTime();
	ActivatedFlag = true;
}

__int64 Time::TimeBomb::Explode(const char* title)
{
	End = unixTime();
	__int64 totTime = End - Start;

	ActivatedFlag = false;

	// Print
	std::cout << title << totTime;
	switch (UnitMode)
	{
	case Sec:
		std::cout << "s";
		break;
	case Ms:
		std::cout << "ms";
		break;
	case Ns:
		std::cout << "ns";
		break;
	default:
		break;
	}
	std::cout << std::endl;

	return End - Start;
}