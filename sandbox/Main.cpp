#include <iostream>
#include <vector>
#include <string>

#include "../../DataStructures/src/time/TimeLib.h"

#include "../include/Vast/Vector.h"
#include "../include/Vast/Utility.h"

template<typename T>
constexpr void LOG(T x) { std::cout << x << std::endl; }

namespace sdtest
{
	int vector()
	{
		Time::TimeBomb tb(1);

		int length = 1'000'000;

		ctl::Vector<int> myArr;
		std::vector<int> stdArr;

		myArr.Reserve(length);
		stdArr.reserve(length);

		for (int i = 0; i < length; i++)
			myArr.PushBack(1);
		for (int i = 0; i < length; i++)
			stdArr.push_back(1);

		tb.Activate();

		for (int i = 0; i < length; i++)
			myArr.Pop();

		tb.Explode("My: ");

		tb.Activate();

		tb.Explode("Std: ");

		std::cout << sizeof(size_t);

		return 1;
	}

	int string()
	{
		return 1;
	}

	int minmax(int length = 1'000'000)
	{
		Time::TimeBomb tb(1);

		tb.Activate();

		for (int i = 0; i < length; i++)
			ctl::min(1, 2);		
		for (int i = 0; i < length; i++)
			ctl::max(1, 2);

		tb.Explode("CTL: ");

		tb.Activate();		

		for (int i = 0; i < length; i++)
			std::min(1, 2);
		for (int i = 0; i < length; i++)
			std::max(1, 2);

		tb.Explode("STD: ");

		return 1;
	}
	int swap(int length = 1'000'000)
	{
		Time::TimeBomb tb(1);

		int a = 1;
		int b = 2;

		tb.Activate();

		for (int i = 0; i < length; i++)
			ctl::swap(a, b);

		tb.Explode("CTL: ");

		tb.Activate();

		for (int i = 0; i < length; i++)
			std::swap(a, b);

		tb.Explode("STD: ");

		return 1;
	}

}

int main()
{
	sdtest::swap(10'000'000);

	return 0;
}