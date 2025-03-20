#include "Gear.h"
#include "./Exception/InvalidGearSpeedLimitsException.h"
#include "./Exception/NegativeGearSpeedException.h"
#include "./Exception/UnCorrectGearTypeWithSpeedLimitsException.h"

Gear::Gear(GearType gearType, std::optional<int> minSpeed, std::optional<int> maxSpeed)
{
	this->m_gearType = gearType;
	this->m_minSpeed = minSpeed;
	this->m_maxSpeed = maxSpeed;
	AssertCorrectGearTypeWithSpeedLimits();
	AssertCorrectSpeedLimits();
}

Gear::Gear(GearType gearType)
{
	this->m_gearType = gearType;
	AssertCorrectGearTypeWithSpeedLimits();
	AssertCorrectSpeedLimits();
}

Gear::Gear()
	: m_gearType(GearType::NEUTRAL)
	, m_minSpeed(std::nullopt)
	, m_maxSpeed(std::nullopt)
{
}

void Gear::AssertCorrectGearTypeWithSpeedLimits()
{
	if (this->m_gearType == GearType::NEUTRAL && (this->m_minSpeed || this->m_maxSpeed)
		|| this->m_gearType != GearType::NEUTRAL && (!this->m_minSpeed || !this->m_maxSpeed))
	{
		throw UnCorrectGearTypeWithSpeedLimitsException();
	}
}

void Gear::AssertCorrectSpeedLimits()
{
	if (this->m_gearType == GearType::NEUTRAL)
	{
		return;
	}
	if (this->m_minSpeed < 0 || this->m_maxSpeed < 0)
	{
		throw NegativeGearSpeedException();
	}
	if (this->m_minSpeed >= this->m_maxSpeed)
	{
		throw InvalidGearSpeedLimitsException();
	}
}

GearType Gear::GetGearType()
{
	return this->m_gearType;
}

std::optional<int> Gear::GetMinSpeed() const
{
	return this->m_minSpeed;
}
std::optional<int> Gear::GetMaxSpeed() const
{
	return this->m_maxSpeed;
}