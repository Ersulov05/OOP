#pragma once
#include <iostream>

class ValueOutOfRangeWhenCalculatingException : public std::runtime_error
{
public:
	ValueOutOfRangeWhenCalculatingException()
		: std::runtime_error("Value out of range when calculating"){};
};