#pragma once
#include <iostream>

class UnknownShapeCommandException : public std::runtime_error
{
public:
	UnknownShapeCommandException()
		: std::runtime_error("Unknown shape command"){};
};