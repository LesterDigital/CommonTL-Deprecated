#include <iostream>
#include <vector>
#include <string>

#include "../../DataStructures/src/time/TimeLib.h"

#include "../include/Vast/Vector.h"

#define LOG(x) std::cout << x << std::endl

int main()
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

	std::string str = "Test.";

	std::cout << sizeof(char);

	return 0;

	tb.Activate();

	for (int i = 0; i < length; i++)
		myArr.Pop();

	tb.Explode("My: ");

	tb.Activate();

	tb.Explode("Std: ");

	std::cout << sizeof(size_t);

	return 0;
}