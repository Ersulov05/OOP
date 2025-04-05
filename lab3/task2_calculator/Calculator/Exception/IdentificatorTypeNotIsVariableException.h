#pragma once
#include <iostream>

class IdentificatorTypeNotIsVariableException : public std::runtime_error
{
public:
	IdentificatorTypeNotIsVariableException()
		: std::runtime_error("Identificator not is variable"){};
};