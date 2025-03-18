#include "ArgUtils.h"
#include "./Exception/InvalidCommandArgumentException.h"

int StringArgToInt(const std::string& string)
{
	int number = 0;
	try
	{
		number = std::stoi(string);
	}
	catch (const std::invalid_argument& e)
	{
		throw InvalidCommandArgumentException();
	}
	catch (const std::out_of_range& e)
	{
		throw InvalidCommandArgumentException();
	}
	return number;
}