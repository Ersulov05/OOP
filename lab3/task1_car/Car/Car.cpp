#include "Car.h"
#include "./Exception/EngineOffGearSettingException.h"
#include "./Exception/EngineOffSpeedSettingException.h"
#include "./Exception/NegativeSpeedException.h"
#include "./Exception/NeutralGearAccelerationException.h"
#include "./Exception/SpeedOutOfGearRangeException.h"
#include "./Exception/UncorrectTurnOffEngineException.h"
#include <iostream>

Car::Car(Transmission& transmission)
	: m_transmission(transmission)
	, m_speed(0)
	, m_direction(Direction::STANDING_STILL)
	, m_engineStatus(false)
{
}

Direction Car::GetDirection() const
{
	return this->m_direction;
}

int Car::GetSpeed() const
{
	return this->m_speed;
}

int Car::GetGear() const
{
	return this->m_transmission.GetCurrentGearNumber();
}

bool Car::GetEngineStatus() const
{
	return this->m_engineStatus;
}

void Car::TurnOnEngine()
{
	this->m_engineStatus = true;
}

void Car::TurnOffEngine()
{
	AssertCorrectTurnOffEngine();
	this->m_engineStatus = false;
}

void Car::SetGear(int gear)
{
	AssertGearShiftingWithEngineOn();
	this->m_transmission.SetGear(gear, this->m_speed, this->m_direction);
}

void Car::SetSpeed(int speed)
{
	Car::AssertSpeedNotNegative(speed);
	AssertSpeedSettingsWithEngineOn();
	Gear currentGear = this->m_transmission.GetCurrentGear();
	if (currentGear.GetGearType() == GearType::NEUTRAL)
	{
		Car::AssertSpeedDecreased(this->m_speed, speed);
	}
	else
	{
		Car::AsserCompatibilitySpeedToGear(speed, currentGear);
	}
	this->m_speed = speed;
	UpdateDirection();
}

void Car::AsserCompatibilitySpeedToGear(int speed, const Gear gear)
{
	if (speed < gear.GetMinSpeed() || gear.GetMaxSpeed() < speed)
	{
		throw SpeedOutOfGearRangeException();
	}
}

void Car::AssertSpeedDecreased(int currentSpeed, int newSpeed)
{
	if (currentSpeed < newSpeed)
	{
		throw NeutralGearAccelerationException();
	}
}

void Car::AssertSpeedNotNegative(int speed)
{
	if (speed < 0)
	{
		throw NegativeSpeedException();
	}
}

void Car::AssertCorrectTurnOffEngine()
{
	Gear currentGear = this->m_transmission.GetCurrentGear();
	if (this->m_speed != 0 || currentGear.GetGearType() != GearType::NEUTRAL)
	{
		throw UncorrectTurnOffEngineException();
	}
}

void Car::AssertSpeedSettingsWithEngineOn()
{
	if (!this->m_engineStatus)
	{
		throw EngineOffSpeedSettingException();
	}
}

void Car::AssertGearShiftingWithEngineOn()
{
	if (!this->m_engineStatus)
	{
		throw EngineOffGearSettingException();
	}
}

void Car::UpdateDirection()
{
	if (this->m_speed == 0)
	{
		this->m_direction = Direction::STANDING_STILL;
		return;
	}

	GearType currentGearType = this->m_transmission.GetCurrentGear().GetGearType();
	switch (currentGearType)
	{
	case GearType::DRIVE:
		this->m_direction = Direction::FORWARD;
		break;
	case GearType::REVERSE:
		this->m_direction = Direction::BACKWARD;
		break;

	default:
		break;
	}
}