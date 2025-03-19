#pragma once
#include <iostream>

class NeutralGearAccelerationException : public std::runtime_error
{
public:
	NeutralGearAccelerationException()
		: std::runtime_error("Cannot accelerate on neutral gear"){};
};
