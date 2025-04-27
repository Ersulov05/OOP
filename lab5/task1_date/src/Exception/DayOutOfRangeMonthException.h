#pragma once
#include <iostream>

class DayOutOfRangeMonthException : public std::out_of_range
{
public:
	DayOutOfRangeMonthException()
		: std::out_of_range("Day out of range month"){};
};