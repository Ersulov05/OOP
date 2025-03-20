#include "Transmission.h"
#include "./Exception/GearsNotLinkedException.h"
#include "./Exception/InvalidGearException.h"
#include "./Exception/NotForwardGearsException.h"
#include "./Exception/UncorrectFirstDriveGearException.h"
#include "./Exception/UncorrectGearshiftException.h"
#include "./Exception/UncorrectReverseGearException.h"
#include "./Exception/UnsuitableCurrentSpeedException.h"
#include <iostream>

Transmission::Transmission(GearSpeedInterval reverseGearSpeedInterval, std::vector<GearSpeedInterval> driveGearsSpeedInterval)
{
	AddReverseGear(reverseGearSpeedInterval);
	AddNeutralGear();
	AddDriveGears(driveGearsSpeedInterval);
	this->m_currentGearNumber = 0;
}

void Transmission::AssertCorrectReverseGearMinSpeed(GearSpeedInterval gearSpeedInterval)
{
	if (gearSpeedInterval.minSpeed != 0)
	{
		throw UncorrectReverseGearException();
	}
}

void Transmission::AssertCorrectFirstDriveGearMinSpeed(GearSpeedInterval gearSpeedInterval)
{
	if (gearSpeedInterval.minSpeed != 0)
	{
		throw UncorrectFirstDriveGearException();
	}
}

void Transmission::AssertGearSpeedIntervalExists(std::vector<GearSpeedInterval> driveGearsSpeedInterval)
{
	if (driveGearsSpeedInterval.size() == 0)
	{
		throw NotForwardGearsException();
	}
}

void Transmission::AssertPreviousGearLinkedCurrentGear(Gear previousGear, Gear currentGear)
{
	if (previousGear.GetMinSpeed() > currentGear.GetMinSpeed() || currentGear.GetMinSpeed() > previousGear.GetMaxSpeed()
		|| previousGear.GetMaxSpeed() >= currentGear.GetMaxSpeed())
	{
		throw GearsNotLinkedException();
	}
}

void Transmission::AddReverseGear(GearSpeedInterval reverseGearSpeedInterval)
{
	AssertCorrectReverseGearMinSpeed(reverseGearSpeedInterval);
	Gear reversGear = Gear(GearType::REVERSE, reverseGearSpeedInterval.minSpeed, reverseGearSpeedInterval.maxSpeed);
	this->m_gears.insert({ -1, reversGear });
}

void Transmission::AddNeutralGear()
{
	Gear neutralGear = Gear(GearType::NEUTRAL);
	this->m_gears.insert({ 0, neutralGear });
}

void Transmission::AddDriveGears(std::vector<GearSpeedInterval> driveGearsSpeedInterval)
{
	AssertGearSpeedIntervalExists(driveGearsSpeedInterval);
	AssertCorrectFirstDriveGearMinSpeed(driveGearsSpeedInterval[0]);
	Gear firstGear = Gear(GearType::DRIVE, driveGearsSpeedInterval[0].minSpeed, driveGearsSpeedInterval[0].maxSpeed);
	this->m_gears.insert({ 1, firstGear });

	Gear previousGear = firstGear;
	for (size_t i = 1; i < driveGearsSpeedInterval.size(); ++i)
	{
		Gear currentGear = Gear(GearType::DRIVE, driveGearsSpeedInterval[i].minSpeed, driveGearsSpeedInterval[i].maxSpeed);
		AssertPreviousGearLinkedCurrentGear(previousGear, currentGear);
		previousGear = currentGear;
		this->m_gears.insert({ i + 1, currentGear });
	}
}

// TODO: сделать приватным и статичным (сделать вначале публичные затем приватные поля)
bool isCorrectEnablingReverseGear(Gear newGear, Direction direction)
{
	return direction == Direction::STANDING_STILL
		|| direction == Direction::FORWARD && newGear.GetGearType() != GearType::REVERSE
		|| direction == Direction::BACKWARD && newGear.GetGearType() != GearType::DRIVE;
}

void Transmission::AssertCorrectGearshift(Gear newGear, int currentSpeed, Direction direction)
{
	Gear currentGear = FindGear(this->m_currentGearNumber);
	if (newGear.GetGearType() == GearType::NEUTRAL)
	{
		return;
	}
	if (!isCorrectEnablingReverseGear(newGear, direction))
	{
		throw UncorrectGearshiftException();
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

	this->m_currentGearNumber = gearNumber;
};

Gear Transmission::FindGear(int gearNumber) const
{
	auto it = this->m_gears.find(gearNumber);
	if (it == this->m_gears.end())
	{
		throw InvalidGearException();
	}
	return it->second;
}

Gear Transmission::GetGear(int gearNumber)
{
	return this->m_gears[gearNumber];
}

Gear Transmission::GetCurrentGear() const
{
	return FindGear(this->m_currentGearNumber);
}

int Transmission::GetCurrentGearNumber() const
{
	return this->m_currentGearNumber;
}