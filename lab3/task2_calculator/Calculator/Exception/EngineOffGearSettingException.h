#pragma once
#include <iostream>

class EngineOffGearSettingException : public std::runtime_error
{
public:
	EngineOffGearSettingException()
		: std::runtime_error("Cannot set gear while engine is off"){};
};