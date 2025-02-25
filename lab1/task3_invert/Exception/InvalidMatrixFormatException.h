#include <iostream>

class InvalidMatrixFormatException : public std::runtime_error
{
public:
	InvalidMatrixFormatException()
		: std::runtime_error("Invalid matrix format"){};
};