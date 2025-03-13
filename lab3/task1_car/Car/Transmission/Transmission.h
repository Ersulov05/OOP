#pragma once
#include "./Gear/Gear.h"
#include <map>
#include <vector>

using MapGearCar = std::map<int, Gear>;

enum class Direction
{
	FORWARD,
	BACKWARD,
	STANDING_STILL,
};

struct GearSpeedInterval
{
	int minSpeed;
	int maxSpeed;
};

class Transmission
{
public:
	Transmission(GearSpeedInterval reverseGear, std::vector<GearSpeedInterval> driveGears);
	void SetGear(int gearNumber, int currentSpeed, Direction direction);

	Gear GetGear(int gearNumber)
	{
		return this->gears[gearNumber];
	}

	int GetCurrentGear() const
	{
		return this->currentGearNumber;
	}

private:
	void AssertCorrectReverseGearMinSpeed(GearSpeedInterval reverseGearSpeedInterval);
	void AssertGearSpeedIntervalExists(std::vector<GearSpeedInterval> driveGearsSpeedInterval);
	void AssertCorrectFirstDriveGearMinSpeed(GearSpeedInterval firstGearSpeedInterval);
	void AssertPreviousGearLinkedCurrentGear(Gear previousGear, Gear currentGear);

	void AssertCorrectGearshift(Gear newGear, int currentSpeed, Direction direction);
	void AddReverseGear(GearSpeedInterval reverseGearSpeedInterval);
	void AddNeutralGear();
	void AddDriveGears(std::vector<GearSpeedInterval> driveGearsSpeedInterval);
	Gear FindGear(int gearNumber);

	MapGearCar gears = {};
	int currentGearNumber = 0;
};