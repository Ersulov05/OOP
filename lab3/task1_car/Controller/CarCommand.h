#pragma once
#include <string>

enum class CarCommand
{
	ENGINE_ON,
	ENGINE_OFF,
	SET_GEAR,
	SET_SPEED,
	INFO,
	UNKNOWN
};

CarCommand GetCarCommandByString(const std::string& string);