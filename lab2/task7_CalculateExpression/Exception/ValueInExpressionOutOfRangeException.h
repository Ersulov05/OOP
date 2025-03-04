#include <iostream>

class ValueInExpressionOutOfRangeException : public std::runtime_error
{
public:
	ValueInExpressionOutOfRangeException()
		: std::runtime_error("Value in expression out of range"){};
};