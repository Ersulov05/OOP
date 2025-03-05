#pragma once
#include <iostream>

class IncorrectExpressionException : public std::runtime_error
{
public:
	IncorrectExpressionException()
		: std::runtime_error("Incorrect expression"){};
};