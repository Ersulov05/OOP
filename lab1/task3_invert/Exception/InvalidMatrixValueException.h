#include <iostream>

class InvalidMatrixValueException : public std::runtime_error
{
public:
	InvalidMatrixValueException()
		: std::runtime_error("Invalid matrix"){};
};