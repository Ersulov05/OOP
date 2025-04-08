#pragma once
#include "./Exception/InvalidConvertStringToValueException.h"
#include "./Exception/ValueOutOfRangeException.h"
#include <iostream>
#include <string>

double GetValueByString(const std::string& string)
{
	size_t pos = 0;
	double value = 0;
	try
	{
		value = std::stod(string, &pos);
	}
	catch (const std::invalid_argument&)
	{
		throw InvalidConvertStringToValueException();
	}
	catch (const std::out_of_range&)
	{
		throw ValueOutOfRangeException();
	}
	if (pos != string.length())
	{
		throw InvalidConvertStringToValueException();
	}

	return value;
}