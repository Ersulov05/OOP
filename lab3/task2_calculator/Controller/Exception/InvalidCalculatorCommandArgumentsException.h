#pragma once
#include <iostream>

class InvalidCalculatorCommandArgumentsException : public std::runtime_error
{
public:
	InvalidCalculatorCommandArgumentsException()
		: std::runtime_error("Invalid calculator command arguments"){};
};