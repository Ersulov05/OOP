#pragma once
#include <iostream>

class InvalidCircleRadiusException : public std::runtime_error
{
public:
	InvalidCircleRadiusException()
		: std::runtime_error("Invalid circle radius"){};
};