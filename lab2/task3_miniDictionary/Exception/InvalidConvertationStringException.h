#ifndef INVALID_CONVERTATION_STRING_EXCEPTION_H
#define INVALID_CONVERTATION_STRING_EXCEPTION_H
#include <iostream>

class InvalidConvertationStringException : public std::runtime_error
{
public:
	InvalidConvertationStringException()
		: std::runtime_error("Invalid convertation string"){};
};
#endif