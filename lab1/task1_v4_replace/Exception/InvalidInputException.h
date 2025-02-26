#include <iostream>

class InvalidInputException : public std::runtime_error
{
public:
	InvalidInputException()
		: std::runtime_error("Invalid input"){};
};