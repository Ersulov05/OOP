#pragma once
#include "./Direction.h"
#include "./Transmission/Transmission.h"

class Car
{
public:
	Car(Transmission transmission);
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
	void UpdateDirection();

	Transmission transmission;
	bool engineStatus;
	Direction direction;
	int speed;
};