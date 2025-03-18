#pragma once
#include <iostream>

class InvalidCommandArgumentException : public std::runtime_error
{
public:
	InvalidCommandArgumentException()
		: std::runtime_error("Invalid command argument"){};
};