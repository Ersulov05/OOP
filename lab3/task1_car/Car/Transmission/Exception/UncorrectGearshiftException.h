#pragma once
#include <iostream>

class UncorrectGearshiftException : public std::runtime_error
{
public:
	UncorrectGearshiftException()
		: std::runtime_error("Uncorrect gearshift"){};
};