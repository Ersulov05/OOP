#include "Gear.h"

Gear::Gear(GearType gearType, std::optional<int> minSpeed, std::optional<int> maxSpeed)
{
	this->gearType = gearType;
	this->minSpeed = minSpeed;
	this->maxSpeed = maxSpeed;
	AssertCorrectGearTypeWithSpeedLimits();
	AssertCorrectSpeedLimits();
}

Gear::Gear(GearType gearType)
{
	this->gearType = gearType;
}

Gear::Gear(const Gear& other)
	: gearType(other.gearType)
	, minSpeed(other.minSpeed)
	, maxSpeed(other.maxSpeed)
{
}

Gear::Gear()
	: gearType(GearType::NEUTRAL)
	, minSpeed(std::nullopt)
	, maxSpeed(std::nullopt)
{
}

void Gear::AssertCorrectGearTypeWithSpeedLimits()
{
}

void Gear::AssertCorrectSpeedLimits()
{
}

GearType Gear::GetGearType()
{
	return this->gearType;
}

std::optional<int> Gear::GetMinSpeed() const
{
	return this->minSpeed;
}
std::optional<int> Gear::GetMaxSpeed() const
{
	return this->maxSpeed;
}