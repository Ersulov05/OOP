#ifndef INVALID_ARGUMENT_COUNT_EXCEPTION_H
#define INVALID_ARGUMENT_COUNT_EXCEPTION_H
#include <iostream>

class InvalidArgumentCountException : public std::runtime_error
{
public:
	InvalidArgumentCountException()
		: std::runtime_error("The number of arguments passed is incorrect"){};
};
#endif