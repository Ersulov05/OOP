#pragma once
#include <iostream>

class DateOutOfRangeException : public std::out_of_range
{
public:
	DateOutOfRangeException()
		: std::out_of_range("Date out of range"){};
};