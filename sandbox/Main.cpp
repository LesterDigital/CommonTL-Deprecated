#include <iostream>
#include <vector>
#include <string>
#include <string_view>

#include "TimeLib.h"

#include "ctl/Vector.h"
#include "ctl/String.h"
#include "ctl/Utility.h"

#define LOG(x) std::cout << x << std::endl
//
//void* operator new(size_t size)
//{
//	std::cout << "Allocating " << size << " bytes" << std::endl;
//
//	return malloc(size);
//}

namespace sdtest // speed tests
{
	int vector(int length = 1'000'000)
	{
		Time::TimeBomb tb(1);

		ctl::Vector<std::int16_t> myArr;
		std::vector<std::int16_t> stdArr;

		std::int16_t a = 2;

		tb.Activate();

		for (int i = 0; i < length; i++)
			myArr.PushBack(a);

		tb.Explode("Ctl: ");

		tb.Activate();

		for (int i = 0; i < length; i++)
			stdArr.push_back(a);

		tb.Explode("Std: ");

		return 1;
	}

	int string(int length = 1'000'000)
	{
		Time::TimeBomb tb(1);

		LOG("Starting...");


		tb.Activate();

		std::string stdstr = "Hello";

		for (int i = 0; i < length; i++)
			stdstr += "hello";

		tb.Explode("Std: ");

		tb.Activate();

		ctl::String ctlstr("Hello");

		for (int i = 0; i < length; i++)
			ctlstr.PushString("hello");

		tb.Explode("Ctl: ");

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

		std::string a = "hi!";
		std::string b = "bye";

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
	// Old - 147 ms
	// Removed \0 - 129 ms
	// "Powers of 2" ReAlloc formula - 119 ms
	
	//sdtest::string();

	using ctl::Vector;

	Vector<Vector<int>> arr1;

	Vector<int> arr;

	arr.PushBack(12);
	arr.PushBack(11);
	arr.PushBack(11);
	arr.PushBack(12);

	arr1.PushBack(arr);
	arr1.PushBack(arr);
	arr1.PushBack(arr);
	arr1.PushBack(arr);

	for (Vector<int> e : arr1)
	{
		for (int e2 : e)
		{
			std::cout << e2 << ' ';
		}
		std::cout << std::endl;
	}

	return 0;
}