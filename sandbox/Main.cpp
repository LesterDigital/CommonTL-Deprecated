#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <string_view>
#include <map>
#include <list>

#include "TimeLib.h"

#include "ctl/Array.h"
#include "ctl/List.h"
#include "ctl/Vector.h"
#include "ctl/String.h"
#include "ctl/Complex.h"
#include "ctl/Utility.h"
#include "ctl/Queue.h"


#define LOG(x) std::cout << x << std::endl

using ctl::Vector;
using ctl::String;

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
	int llist(int length = 1'000'000)
	{
		{
			Time::ScopedTimer stimer;

			std::list<int> stdlist;

			for (int i = 0; i < length; i++)
				stdlist.push_back(i + 1);			
			for (int i = 0; i < length; i++)
				stdlist.pop_back();

			std::cout << "Std linked list: ";
		}
		{
			Time::ScopedTimer stimer;

			ctl::List<int> ctllist;

			for (int i = 0; i < length; i++)
				ctllist.PushBack(i + 1);
			for (int i = 0; i < length; i++)
				ctllist.PopBack();

			std::cout << "Ctl linked list: ";
		}

		return 0;
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

	sdtest::llist();

	//std::list<int> stdlist;
	//ctl::List<int> llist;

	//for (int i = 0; i < 10; i++)
	//	llist.PushBack(i + 1);

	//llist.PopFront();

	//llist.PopBack();

	//for (const auto& item : llist)
	//	std::cout << item << ' ';
	//std::cout << std::endl;

	return 0;
}