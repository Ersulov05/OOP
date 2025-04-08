#pragma once
#include <iostream>

class InvalidConvertStringToValueException : public std::runtime_error
{
public:
	InvalidConvertStringToValueException()
		: std::runtime_error("Invalid convert string to value"){};
};