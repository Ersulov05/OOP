#include "Car.h"

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
	int currentGearNumber = this->transmission.GetCurrentGear();
	GearType currentGearType = this->transmission.GetGear(currentGearNumber).GetGearType();
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
	return this->transmission.GetCurrentGear();
}

bool Car::GetEngineStatus()
{
	return this->engineStatus;
}