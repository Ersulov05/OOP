#pragma once
#include <iostream>

class EngineOffSpeedSettingException : public std::runtime_error
{
public:
	EngineOffSpeedSettingException()
		: std::runtime_error("Cannot set speed while engine is off"){};
};
