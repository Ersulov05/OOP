#include "Operation.h"
#include <cmath>

Operation GetOperationByString(const std::string& str)
{
	if (str == "+")
	{
		return Operation::PLUS;
	}
	else if (str == "-")
	{
		return Operation::MINUS;
	}
	else if (str == "*")
	{
		return Operation::MULTIPLY;
	}
	else if (str == "/")
	{
		return Operation::DIVIDING;
	}
	return Operation::NONE;
}

float ExecuteOperation(Operation operation, float firstArgument, float secondArgument)
{
	switch (operation)
	{
	case Operation::PLUS:
		return firstArgument + secondArgument;
	case Operation::MINUS:
		return firstArgument - secondArgument;
	case Operation::MULTIPLY:
		return firstArgument * secondArgument;
	case Operation::DIVIDING:
		return secondArgument != 0
			? firstArgument / secondArgument
			: NAN;
	default:
		return NAN;
	}
}