#pragma once
#include <iostream>

class InvalidTriangleException : public std::runtime_error
{
public:
	InvalidTriangleException()
		: std::runtime_error("Invalid triangle"){};
};