#pragma once
#include <iostream>

class InvalidRectangleSizeException : public std::runtime_error
{
public:
	InvalidRectangleSizeException()
		: std::runtime_error("Invalid rectangle size"){};
};