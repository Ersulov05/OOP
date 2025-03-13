#pragma once
#include "./Transmission/Transmission.h"

class Car
{
public:
	Car(Transmission transmission);
	bool TurnOnEngine();
	bool TurnOffEngine();
	void SetGear(int gear);
	void SetSpeed(int speed);
	Direction GetDirection();
	int GetSpeed() const;
	int GetGear() const;
	bool GetEngineStatus();

private:
	void AssertEngineOn();
	void UpdateDirection();
	Transmission transmission;
	bool engineStatus;
	Direction direction;
	int speed;
};