#pragma once
#include <iostream>

class UnCorrectGearshiftException : public std::runtime_error
{
public:
	UnCorrectGearshiftException()
		: std::runtime_error("Uncorrect gearshift"){};
};