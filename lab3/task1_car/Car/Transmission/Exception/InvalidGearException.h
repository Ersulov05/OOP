#pragma once
#include <iostream>

class InvalidGearException : public std::runtime_error
{
public:
	InvalidGearException()
		: std::runtime_error("Invalid gear"){};
};