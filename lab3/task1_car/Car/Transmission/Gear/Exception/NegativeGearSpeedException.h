#pragma once
#include <iostream>

class NegativeGearSpeedException : public std::logic_error
{
public:
	NegativeGearSpeedException()
		: std::logic_error("Negative gear speed"){};
};