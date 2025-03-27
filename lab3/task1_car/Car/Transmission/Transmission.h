#pragma once
#include "../Direction.h"
#include "./Gear/Gear.h"
#include <map>
#include <vector>

using MapGearCar = std::map<int, Gear>;

struct GearSpeedInterval
{
	int minSpeed;
	int maxSpeed;
};

class Transmission
{
public:
	explicit Transmission(GearSpeedInterval reverseGear, std::vector<GearSpeedInterval> driveGears);
	void SetGear(int gearNumber, int currentSpeed, Direction direction);
	Gear GetGear(int gearNumber);
	Gear GetCurrentGear() const;
	int GetCurrentGearNumber() const;

private:
	void AssertCorrectReverseGearMinSpeed(GearSpeedInterval reverseGearSpeedInterval);
	void AssertGearSpeedIntervalExists(std::vector<GearSpeedInterval> driveGearsSpeedInterval);
	void AssertCorrectFirstDriveGearMinSpeed(GearSpeedInterval firstGearSpeedInterval);
	void AssertPreviousGearLinkedCurrentGear(Gear previousGear, Gear currentGear);
	bool static IsCorrectEnablingReverseGear(Gear newGear, Direction direction);

	void AssertCorrectGearshift(Gear newGear, int currentSpeed, Direction direction);
	void AddReverseGear(GearSpeedInterval reverseGearSpeedInterval);
	void AddNeutralGear();
	void AddDriveGears(std::vector<GearSpeedInterval> driveGearsSpeedInterval);
	Gear FindGear(int gearNumber) const;

	MapGearCar m_gears = {};
	int m_currentGearNumber = 0;
};