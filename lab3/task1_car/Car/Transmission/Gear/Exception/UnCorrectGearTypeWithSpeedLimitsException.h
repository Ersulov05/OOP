#pragma once
#include <iostream>

class UnCorrectGearTypeWithSpeedLimitsException : public std::logic_error
{
public:
	UnCorrectGearTypeWithSpeedLimitsException()
		: std::logic_error("UnCorrect GearType with speed limits"){};
};