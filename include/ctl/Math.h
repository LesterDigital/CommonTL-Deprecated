#pragma once

#ifndef CTL_MATH_H
#define CTL_MATH_H

#include <random>

#include "Types.h"

namespace ctl::Math
{
	class RadomEngine
	{
	public:
		// Returns a pseudorandom number in a given range
		static uint32 Randint(uint32 left, uint32 right);
	public:

	private:
		uint32 m_Seed;
	};

	void Test()
	{
		std::default_random_engine eng();
	}
}

#endif