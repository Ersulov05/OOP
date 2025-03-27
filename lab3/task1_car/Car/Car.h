#pragma once
#include "./Direction.h"
#include "./Transmission/Transmission.h"

class Car
{
public:
	explicit Car(Transmission& transmission);
	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(int gear);
	void SetSpeed(int speed);
	Direction GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;
	bool GetEngineStatus() const;

private:
	void AssertCorrectTurnOffEngine();
	void AssertSpeedSettingsWithEngineOn();
	void AssertGearShiftingWithEngineOn();
	void static AsserCompatibilitySpeedToGear(int speed, const Gear gear);
	void static AssertSpeedDecreased(int currentSpeed, int newSpeed);
	void static AssertSpeedNotNegative(int speed);
	void UpdateDirection();

	Transmission& m_transmission;
	bool m_engineStatus;
	Direction m_direction;
	int m_speed;
};