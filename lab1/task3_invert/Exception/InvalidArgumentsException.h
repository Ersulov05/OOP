#include <iostream>

class InvalidArgumentsException : public std::runtime_error
{
public:
	InvalidArgumentsException()
		: std::runtime_error("The number of arguments passed is incorrect"){};
};