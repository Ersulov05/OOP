#include "CarController.h"
#include "../Utils/ArgUtils.h"
#include <iostream>
#include <string>

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
	else if (string == "Exit")
	{
		return CarCommand::EXIT;
	}
	else if (string == "Info")
	{
		return CarCommand::INFO;
	}
	return CarCommand::UNKNOWN;
}

void PrintCarInfo(std::ostream& output, const Car& car)
{
	output << "speed: " << car.GetSpeed() << std::endl;
	output << "gear: " << car.GetGear() << std::endl;
}

void AssertCountArgs(int expectedCount, const std::vector<std::string>& stringArgs)
{
	if (stringArgs.size() != expectedCount)
	{
		// error count args
	}
}

void SetCarSpeed(Car& car, const std::vector<std::string>& stringArgs)
{
	AssertCountArgs(1, stringArgs);
	int speed = StringArgToInt(stringArgs[0]);
	car.SetSpeed(speed);
}

void SetCarGear(Car& car, const std::vector<std::string>& stringArgs)
{
	AssertCountArgs(1, stringArgs);
	int gear = StringArgToInt(stringArgs[0]);
	car.SetGear(gear);
}

bool ProcessCarCommand(std::ostream& output, Car& car, CarCommand command, const std::vector<std::string>& stringArgs)
{
	try
	{
		switch (command)
		{
		case CarCommand::EXIT:
			return true;
		case CarCommand::INFO:
			PrintCarInfo(output, car);
			break;
		case CarCommand::SET_SPEED:
			SetCarSpeed(car, stringArgs);
			break;
		case CarCommand::SET_GEAR:
			SetCarGear(car, stringArgs);
			break;
		default:
			break;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return false;
}