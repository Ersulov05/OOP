#pragma once
#include "./Exception/InvalidConvertStringToValueException.h"
#include "./Exception/ValueOutOfRangeException.h"
#include <iostream>
#include <limits>
#include <string>

double GetDoubleValueByString(const std::string& string)
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

unsigned int GetUIntValueByString(const std::string& string)
{
	if (string.empty() || string[0] == '-')
	{
		throw InvalidConvertStringToValueException();
	}

	size_t start = string.find_first_not_of(" \t");
	if (start == std::string::npos)
	{
		throw InvalidConvertStringToValueException();
	}

	size_t pos = 0;
	unsigned long value = 0;

	try
	{
		value = std::stoul(string, &pos, 0);
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
	if (value > std::numeric_limits<unsigned int>::max())
	{
		throw ValueOutOfRangeException();
	}

	return static_cast<unsigned int>(value);
}