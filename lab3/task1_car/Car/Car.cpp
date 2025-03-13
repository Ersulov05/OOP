#include "Car.h"
#include <iostream>

Car::Car(Transmission transmission)
	: transmission(transmission)
	, speed(0)
	, direction(Direction::STANDING_STILL)
	, engineStatus(false)
{
}

bool Car::TurnOnEngine()
{
	this->engineStatus = true;
	return true;
}

bool Car::TurnOffEngine()
{
	this->engineStatus = false;
	return true;
}

void Car::SetGear(int gear)
{
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

void AsserCompatibilitySpeedToGear(int speed, const Gear gear)
{
	if (speed < gear.GetMinSpeed() || gear.GetMaxSpeed() < speed)
	{
		throw std::runtime_error("Speed is out of gear range");
	}
}

void AssertSpeedDecreased(int currentSpeed, int newSpeed)
{
	if (currentSpeed < newSpeed)
	{
		throw std::runtime_error("Cannot accelerate on neutral");
	}
}

void AssertSpeedNotNegative(int speed)
{
	if (speed < 0)
	{
		throw std::runtime_error("Speed cannot be negative");
	}
}

void Car::AssertEngineOn()
{
	if (!this->engineStatus)
	{
		throw std::runtime_error("Cannot set speed while engine is off");
	}
}

void Car::SetSpeed(int speed)
{
	AssertSpeedNotNegative(speed);
	AssertEngineOn();
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

Direction Car::GetDirection()
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

bool Car::GetEngineStatus()
{
	return this->engineStatus;
}