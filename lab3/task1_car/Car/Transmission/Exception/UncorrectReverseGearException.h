#pragma once
#include <iostream>

class UncorrectReverseGearException : public std::logic_error
{
public:
	UncorrectReverseGearException()
		: std::logic_error("Uncorrect reverse gear"){};
};