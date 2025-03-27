#pragma once
#include <iostream>

class UncorrectFirstDriveGearException : public std::logic_error
{
public:
	UncorrectFirstDriveGearException()
		: std::logic_error("Uncorrect first drive gear"){};
};