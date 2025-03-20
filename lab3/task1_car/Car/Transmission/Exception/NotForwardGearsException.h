#pragma once
#include <iostream>

class NotForwardGearsException : public std::logic_error
{
public:
	NotForwardGearsException()
		: std::logic_error("Not forward gears"){};
};