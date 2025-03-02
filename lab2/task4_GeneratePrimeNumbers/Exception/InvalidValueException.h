#include <iostream>

class InvalidValueException : public std::runtime_error
{
public:
	InvalidValueException()
		: std::runtime_error("Invalid Value"){};
};