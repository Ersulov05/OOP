#include "Operation.h"

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