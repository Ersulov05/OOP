#pragma once
#include <iostream>

class UnsuitableCurrentSpeedException : public std::runtime_error
{
public:
	UnsuitableCurrentSpeedException()
		: std::runtime_error("Unsuitable current speed"){};
};