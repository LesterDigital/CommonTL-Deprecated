#pragma once

#ifndef CTL_UTILITY_H
#define CTL_UTILITY_H

namespace ctl
{
	// Returns the lowest of the given parameters
	template<typename Ty>
	constexpr inline const Ty& min(const Ty& a, const Ty& b)
	{
		return (a < b) ? a : b;
	}

	// Returns the greatest of the given parameters
	template<typename Ty>
	constexpr inline const Ty& max(const Ty& a, const Ty& b)
	{
		return (a > b) ? a : b;
	}

	template<typename Ty>
	inline void swap(Ty& a, Ty& b)
	{
		Ty tmp = a;
		a = b;
		b = tmp;
	}
}

#endif