#pragma once
#include <iostream>

class IdentificatorNotFoundException : public std::runtime_error
{
public:
	IdentificatorNotFoundException()
		: std::runtime_error("Identificator not found"){};
};