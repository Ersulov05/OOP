#pragma once
#include <iostream>

class IdentificatorNameExistsException : public std::runtime_error
{
public:
	IdentificatorNameExistsException()
		: std::runtime_error("Identificator name exists"){};
};