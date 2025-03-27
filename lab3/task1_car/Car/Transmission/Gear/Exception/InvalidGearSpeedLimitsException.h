#pragma once
#include <iostream>

class InvalidGearSpeedLimitsException : public std::logic_error
{
public:
	InvalidGearSpeedLimitsException()
		: std::logic_error("Invalid gear speed limits"){};
};