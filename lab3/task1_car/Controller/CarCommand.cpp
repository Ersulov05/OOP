#include "CarCommand.h"

CarCommand GetCarCommandByString(const std::string& string)
{
	if (string == "EngineOn")
	{
		return CarCommand::ENGINE_ON;
	}
	else if (string == "EngineOff")
	{
		return CarCommand::ENGINE_OFF;
	}
	else if (string == "SetGear")
	{
		return CarCommand::SET_GEAR;
	}
	else if (string == "SetSpeed")
	{
		return CarCommand::SET_SPEED;
	}
	else if (string == "Info")
	{
		return CarCommand::INFO;
	}
	return CarCommand::UNKNOWN;
}