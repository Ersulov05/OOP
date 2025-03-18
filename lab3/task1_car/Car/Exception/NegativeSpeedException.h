#pragma once
#include <iostream>

class NegativeSpeedException : public std::runtime_error
{
public:
	NegativeSpeedException()
		: std::runtime_error("Speed cannot be negative"){};
};