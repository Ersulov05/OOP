#include "ArgUtils.h"
#include "../Exception/ValueOutOfRangeException.h"

int StringArgToInt(const std::string& string)
{
	int number = 0;
	try
	{
		number = std::stoi(string);
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "error" << std::endl;
		// error Invalid command argument
	}
	catch (const std::out_of_range& e)
	{
		std::cout << "error" << std::endl;
		// error Invalid command argument
	}
	return number;
}