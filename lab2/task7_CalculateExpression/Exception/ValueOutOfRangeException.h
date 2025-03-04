#include <iostream>
#include <string>

class ValueOutOfRangeException : public std::runtime_error
{
public:
	ValueOutOfRangeException()
		: std::runtime_error("Value out of range"){};
};