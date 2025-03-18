#pragma once
#include <iostream>

class InvalidCountArgsException : public std::runtime_error
{
public:
	InvalidCountArgsException()
		: std::runtime_error("Invalid count args"){};
};