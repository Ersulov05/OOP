#include "CarController.h"
#include "../Car/Direction.h"
#include "../Car/Exception/EngineOffGearSettingException.h"
#include "../Car/Exception/EngineOffSpeedSettingException.h"
#include "../Car/Exception/NegativeSpeedException.h"
#include "../Car/Exception/NeutralGearAccelerationException.h"
#include "../Car/Exception/SpeedOutOfGearRangeException.h"
#include "../Car/Exception/UncorrectTurnOffEngineException.h"
#include "../Car/Transmission/Exception/InvalidGearException.h"
#include "../Car/Transmission/Exception/UncorrectGearshiftException.h"
#include "../Car/Transmission/Exception/UnsuitableCurrentSpeedException.h"
#include "../Utils/ArgUtils.h"
#include "../Utils/Exception/InvalidCommandArgumentException.h"
#include "./Exception/InvalidCountArgsException.h"
#include <iostream>
#include <string>

CarController::CarController(Car car)
	: m_car(car){};

void AssertCountArgs(int expectedCount, const std::vector<std::string>& stringArgs)
{
	if (stringArgs.size() != expectedCount)
	{
		throw InvalidCountArgsException();
	}
}

void CarController::PrintCarInfo(std::ostream& output)
{
	output << "---------------" << std::endl;
	output << "speed: " << this->m_car.GetSpeed() << std::endl;
	output << "gear: " << this->m_car.GetGear() << std::endl;
	output << "engine: " << (this->m_car.GetEngineStatus() ? "On" : "Off") << std::endl;
	output << "direction: " << ConvertDirectionToString(this->m_car.GetDirection()) << std::endl;
	output << "---------------" << std::endl;
}

void CarController::SetCarSpeed(const std::vector<std::string>& stringArgs)
{
	AssertCountArgs(1, stringArgs);
	int speed = StringArgToInt(stringArgs[0]);
	this->m_car.SetSpeed(speed);
}

void CarController::SetCarGear(const std::vector<std::string>& stringArgs)
{
	AssertCountArgs(1, stringArgs);
	int gear = StringArgToInt(stringArgs[0]);
	this->m_car.SetGear(gear);
}

void CarController::ExecuteCarCommand(std::ostream& output, CarCommand command, const std::vector<std::string>& stringArgs)
{
	switch (command)
	{
	case CarCommand::INFO:
		PrintCarInfo(output);
		break;
	case CarCommand::SET_SPEED:
		SetCarSpeed(stringArgs);
		break;
	case CarCommand::SET_GEAR:
		SetCarGear(stringArgs);
		break;
	case CarCommand::ENGINE_ON:
		this->m_car.TurnOnEngine();
		break;
	case CarCommand::ENGINE_OFF:
		this->m_car.TurnOffEngine();
		break;
	default:
		output << "Unknown command" << std::endl;
		break;
	}
}

void handleException(const std::exception& e)
{
	std::cout << e.what() << std::endl;
}

void CarController::ProcessCarCommand(std::ostream& output, CarCommand command, const std::vector<std::string>& stringArgs)
{
	try
	{
		this->ExecuteCarCommand(output, command, stringArgs);
	}
	catch (const EngineOffGearSettingException& e)
	{
		handleException(e);
	}
	catch (const EngineOffSpeedSettingException& e)
	{
		handleException(e);
	}
	catch (const NegativeSpeedException& e)
	{
		handleException(e);
	}
	catch (const NeutralGearAccelerationException& e)
	{
		handleException(e);
	}
	catch (const SpeedOutOfGearRangeException& e)
	{
		handleException(e);
	}
	catch (const InvalidCountArgsException& e)
	{
		handleException(e);
	}
	catch (const InvalidCommandArgumentException& e)
	{
		handleException(e);
	}
	catch (const InvalidGearException& e)
	{
		handleException(e);
	}
	catch (const UncorrectGearshiftException& e)
	{
		handleException(e);
	}
	catch (const UnsuitableCurrentSpeedException& e)
	{
		handleException(e);
	}
	catch (const UncorrectTurnOffEngineException& e)
	{
		handleException(e);
	}
}

Car CarController::GetCar() const
{
	return this->m_car;
}