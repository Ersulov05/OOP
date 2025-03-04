#include <iostream>

class InvalidExpressionException : public std::runtime_error
{
public:
	InvalidExpressionException()
		: std::runtime_error("Invalid expression"){};
};