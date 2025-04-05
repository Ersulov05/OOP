#pragma once
#include <iostream>

class UnknownCalculatorCommandException : public std::runtime_error
{
public:
	UnknownCalculatorCommandException()
		: std::runtime_error("Unknown calculator command"){};
};