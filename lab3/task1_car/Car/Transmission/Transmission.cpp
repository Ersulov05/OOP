#include "Transmission.h"
#include "./Exception/InvalidGearException.h"
#include "./Exception/UnCorrectGearshiftException.h"
#include "./Exception/UnsuitableCurrentSpeedException.h"
#include <iostream>

Transmission::Transmission(GearSpeedInterval reverseGearSpeedInterval, std::vector<GearSpeedInterval> driveGearsSpeedInterval)
{
	AddReverseGear(reverseGearSpeedInterval);
	AddNeutralGear();
	AddDriveGears(driveGearsSpeedInterval);
	this->currentGearNumber = 0;
}

void Transmission::AssertCorrectReverseGearMinSpeed(GearSpeedInterval gearSpeedInterval)
{
	if (gearSpeedInterval.minSpeed != 0)
	{
		// error
	}
}

void Transmission::AssertCorrectFirstDriveGearMinSpeed(GearSpeedInterval gearSpeedInterval)
{
	if (gearSpeedInterval.minSpeed != 0)
	{
		// error
	}
}

void Transmission::AssertGearSpeedIntervalExists(std::vector<GearSpeedInterval> driveGearsSpeedInterval)
{
	if (driveGearsSpeedInterval.size() == 0)
	{
		// error
	}
}

void Transmission::AssertPreviousGearLinkedCurrentGear(Gear previousGear, Gear currentGear)
{
	// проверка связанности передач
}

void Transmission::AddReverseGear(GearSpeedInterval reverseGearSpeedInterval)
{
	AssertCorrectReverseGearMinSpeed(reverseGearSpeedInterval);
	Gear reversGear = Gear(GearType::REVERSE, reverseGearSpeedInterval.minSpeed, reverseGearSpeedInterval.maxSpeed);
	this->gears.insert({ -1, reversGear });
}

void Transmission::AddNeutralGear()
{
	Gear neutralGear = Gear(GearType::NEUTRAL);
	this->gears.insert({ 0, neutralGear });
}

void Transmission::AddDriveGears(std::vector<GearSpeedInterval> driveGearsSpeedInterval)
{
	AssertGearSpeedIntervalExists(driveGearsSpeedInterval);
	AssertCorrectFirstDriveGearMinSpeed(driveGearsSpeedInterval[0]);
	Gear firstGear = Gear(GearType::DRIVE, driveGearsSpeedInterval[0].minSpeed, driveGearsSpeedInterval[0].maxSpeed);
	this->gears.insert({ 1, firstGear });

	Gear previousGear = firstGear;
	for (size_t i = 1; i < driveGearsSpeedInterval.size(); ++i)
	{
		Gear currentGear = Gear(GearType::DRIVE, driveGearsSpeedInterval[i].minSpeed, driveGearsSpeedInterval[i].maxSpeed);
		AssertPreviousGearLinkedCurrentGear(previousGear, currentGear);
		this->gears.insert({ i + 1, currentGear });
	}
}

bool isCorrectEnablingReverseGear(Gear newGear, Direction direction)
{
	return direction == Direction::STANDING_STILL
		|| direction == Direction::FORWARD && newGear.GetGearType() != GearType::REVERSE
		|| direction == Direction::BACKWARD && newGear.GetGearType() != GearType::DRIVE;
}

void Transmission::AssertCorrectGearshift(Gear newGear, int currentSpeed, Direction direction)
{
	Gear currentGear = FindGear(this->currentGearNumber);
	if (!isCorrectEnablingReverseGear(newGear, direction))
	{
		throw UnCorrectGearshiftException();
	}
	if (currentSpeed < newGear.GetMinSpeed().value() || newGear.GetMaxSpeed().value() < currentSpeed)
	{
		throw UnsuitableCurrentSpeedException();
	}
}

void Transmission::SetGear(int gearNumber, int currentSpeed, Direction direction)
{
	Gear gear = FindGear(gearNumber);
	AssertCorrectGearshift(gear, currentSpeed, direction);

	this->currentGearNumber = gearNumber;
};

Gear Transmission::FindGear(int gearNumber)
{
	auto it = gears.find(gearNumber);
	if (it == gears.end())
	{
		throw InvalidGearException();
	}
	return it->second;
}