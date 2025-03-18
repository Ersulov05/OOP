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
	Gear(GearType gearType, std::optional<int> minSpeed, std::optional<int> maxSpeed);
	Gear(GearType gearType);
	Gear(const Gear& other);
	Gear();
	~Gear(){};
	GearType GetGearType();
	std::optional<int> GetMinSpeed() const;
	std::optional<int> GetMaxSpeed() const;

private:
	void AssertCorrectGearTypeWithSpeedLimits();
	void AssertCorrectSpeedLimits();
	GearType gearType;
	std::optional<int> minSpeed;
	std::optional<int> maxSpeed;
};