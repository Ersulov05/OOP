#include "src/CMyString.h"
#include <iostream>

int main()
{
	CMyString string = "999";
	auto x = string;
	string = string;
	x += "090000000000";
	// x = "00";
	x[0] = 'H';
	auto a = x + string;
	std::cout << string << " " << x << x[1] << std::endl;
	std::cout << a;

	return 0;
}