#pragma once
#include <iostream>

class SpeedOutOfGearRangeException : public std::runtime_error
{
public:
	SpeedOutOfGearRangeException()
		: std::runtime_error("Speed is out of gear range"){};
};