#include "Car.h"
#include "./Exception/EngineOffGearSettingException.h"
#include "./Exception/EngineOffSpeedSettingException.h"
#include "./Exception/NegativeSpeedException.h"
#include "./Exception/NeutralGearAccelerationException.h"
#include "./Exception/SpeedOutOfGearRangeException.h"
#include "./Exception/UnCorrectTurnOffEngine.h"
#include <iostream>

Car::Car(Transmission transmission)
	: transmission(transmission)
	, speed(0)
	, direction(Direction::STANDING_STILL)
	, engineStatus(false)
{
}

void AsserCompatibilitySpeedToGear(int speed, const Gear gear)
{
	if (speed < gear.GetMinSpeed() || gear.GetMaxSpeed() < speed)
	{
		throw SpeedOutOfGearRangeException();
	}
}

void AssertSpeedDecreased(int currentSpeed, int newSpeed)
{
	if (currentSpeed < newSpeed)
	{
		throw NeutralGearAccelerationException();
	}
}

void AssertSpeedNotNegative(int speed)
{
	if (speed < 0)
	{
		throw NegativeSpeedException();
	}
}

void Car::AssertCorrectTurnOffEngine()
{
	Gear currentGear = this->transmission.GetCurrentGear();
	if (this->speed != 0 || currentGear.GetGearType() != GearType::NEUTRAL)
	{
		throw UnCorrectTurnOffEngine();
	}
}

void Car::AssertSpeedSettingsWithEngineOn()
{
	if (!this->engineStatus)
	{
		throw EngineOffSpeedSettingException();
	}
}

void Car::AssertGearShiftingWithEngineOn()
{
	if (!this->engineStatus)
	{
		throw EngineOffGearSettingException();
	}
}

void Car::TurnOnEngine()
{
	this->engineStatus = true;
}

void Car::TurnOffEngine()
{
	AssertCorrectTurnOffEngine();
	this->engineStatus = false;
}

void Car::SetGear(int gear)
{
	AssertGearShiftingWithEngineOn();
	this->transmission.SetGear(gear, this->speed, this->direction);
}

void Car::UpdateDirection()
{
	if (this->speed == 0)
	{
		this->direction = Direction::STANDING_STILL;
		return;
	}

	GearType currentGearType = this->transmission.GetCurrentGear().GetGearType();
	switch (currentGearType)
	{
	case GearType::DRIVE:
		this->direction = Direction::FORWARD;
		break;
	case GearType::REVERSE:
		this->direction = Direction::BACKWARD;
		break;

	default:
		break;
	}
}

void Car::SetSpeed(int speed)
{
	AssertSpeedNotNegative(speed);
	AssertSpeedSettingsWithEngineOn();
	Gear currentGear = this->transmission.GetCurrentGear();
	if (currentGear.GetGearType() == GearType::NEUTRAL)
	{
		AssertSpeedDecreased(this->speed, speed);
	}
	else
	{
		AsserCompatibilitySpeedToGear(speed, currentGear);
	}
	this->speed = speed;
	UpdateDirection();
}

Direction Car::GetDirection() const
{
	return this->direction;
}

int Car::GetSpeed() const
{
	return this->speed;
}

int Car::GetGear() const
{
	return this->transmission.GetCurrentGearNumber();
}

bool Car::GetEngineStatus() const
{
	return this->engineStatus;
}