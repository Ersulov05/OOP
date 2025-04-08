#pragma once
#include <iostream>

class InvalidCountArgumentsException : public std::runtime_error
{
public:
	InvalidCountArgumentsException()
		: std::runtime_error("Invalid count arguments"){};
};