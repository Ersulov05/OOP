#pragma once
#include <optional>

enum class GearType
{
	REVERSE,
	NEUTRAL,
	DRIVE
};

class Gear
{
public:
	explicit Gear(GearType gearType, std::optional<int> minSpeed, std::optional<int> maxSpeed);
	explicit Gear(GearType gearType);
	Gear();
	GearType GetGearType();
	std::optional<int> GetMinSpeed() const;
	std::optional<int> GetMaxSpeed() const;

private:
	void AssertCorrectGearTypeWithSpeedLimits();
	void AssertCorrectSpeedLimits();
	GearType m_gearType;
	std::optional<int> m_minSpeed;
	std::optional<int> m_maxSpeed;
};