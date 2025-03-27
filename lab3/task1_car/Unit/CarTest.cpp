#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Car/Car.h"
#include "../Car/Exception/EngineOffGearSettingException.h"
#include "../Car/Exception/EngineOffSpeedSettingException.h"
#include "../Car/Exception/NegativeSpeedException.h"
#include "../Car/Exception/NeutralGearAccelerationException.h"
#include "../Car/Exception/SpeedOutOfGearRangeException.h"
#include "../Car/Exception/UncorrectTurnOffEngineException.h"
#include "../Car/Transmission/Exception/InvalidGearException.h"
#include "../Car/Transmission/Exception/UncorrectGearshiftException.h"
#include "../Car/Transmission/Exception/UnsuitableCurrentSpeedException.h"

const int MIN_SPEED_REVERSE_GEAR = 0;
const int MAX_SPEED_REVERSE_GEAR = 20;
const int MIN_SPEED_FIRST_GEAR = 0;
const int MAX_SPEED_FIRST_GEAR = 30;
const int MIN_SPEED_SECOND_GEAR = 20;
const int MAX_SPEED_SECOND_GEAR = 50;

Transmission CreateTransmission()
{
	GearSpeedInterval reverseGearSpeedInterval = { MIN_SPEED_REVERSE_GEAR, MAX_SPEED_REVERSE_GEAR };
	std::vector<GearSpeedInterval> driveGearSpeedIntervals = {
		{ MIN_SPEED_FIRST_GEAR, MAX_SPEED_FIRST_GEAR },
		{ MIN_SPEED_SECOND_GEAR, MAX_SPEED_SECOND_GEAR }
	};
	return Transmission(reverseGearSpeedInterval, driveGearSpeedIntervals);
}

TEST_CASE("TestCarTurnOnOffEngineSuccess")
{
	Transmission transmission = CreateTransmission();
	Car car(transmission);

	REQUIRE(car.GetEngineStatus() == false);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);

	car.TurnOnEngine();
	REQUIRE(car.GetEngineStatus() == true);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);

	car.TurnOffEngine();
	REQUIRE(car.GetEngineStatus() == false);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);
}

// TODO: Для каждой передачи протестировать границы
TEST_CASE("TestSetGearAndSetSpeedWithFiveGears")
{
	int reverseGearMinSpeed = 0;
	int reverseGearMaxSpeed = 20;
	int firstGearMinSpeed = 0;
	int firstGearMaxSpeed = 30;
	int secondGearMinSpeed = 20;
	int secondGearMaxSpeed = 50;
	int thirdGearMinSpeed = 30;
	int thirdGearMaxSpeed = 60;
	int fourthGearMinSpeed = 40;
	int fourthGearMaxSpeed = 90;
	int fifthGearMinSpeed = 50;
	int fifthGearMaxSpeed = 150;
	GearSpeedInterval reverseGearSpeedInterval = { reverseGearMinSpeed, reverseGearMaxSpeed };
	std::vector<GearSpeedInterval> driveGearSpeedIntervals = {
		{ firstGearMinSpeed, firstGearMaxSpeed },
		{ secondGearMinSpeed, secondGearMaxSpeed },
		{ thirdGearMinSpeed, thirdGearMaxSpeed },
		{ fourthGearMinSpeed, fourthGearMaxSpeed },
		{ fifthGearMinSpeed, fifthGearMaxSpeed }
	};

	Transmission transmission(reverseGearSpeedInterval, driveGearSpeedIntervals);
	Car car(transmission);
	car.TurnOnEngine();
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);

	// reverse Gear
	car.SetGear(-1);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == -1);

	car.SetSpeed(reverseGearMaxSpeed);
	REQUIRE(car.GetSpeed() == reverseGearMaxSpeed);

	REQUIRE_THROWS_AS(car.SetSpeed(reverseGearMaxSpeed + 1), SpeedOutOfGearRangeException);
	REQUIRE_THROWS_AS(car.SetSpeed(reverseGearMinSpeed - 1), NegativeSpeedException);
	REQUIRE_THROWS_AS(car.SetGear(1), UncorrectGearshiftException);
	REQUIRE_THROWS_AS(car.SetGear(-2), InvalidGearException);

	// neutral Gear
	car.SetGear(0);
	REQUIRE(car.GetSpeed() == reverseGearMaxSpeed);
	REQUIRE(car.GetGear() == 0);

	car.SetSpeed(0);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE_THROWS_AS(car.SetGear(2), UnsuitableCurrentSpeedException);

	// first Gear
	car.SetGear(1);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 1);

	car.SetSpeed(firstGearMinSpeed);
	REQUIRE(car.GetSpeed() == firstGearMinSpeed);
	REQUIRE_THROWS_AS(car.SetGear(2), UnsuitableCurrentSpeedException);

	car.SetSpeed(firstGearMaxSpeed);
	REQUIRE(car.GetSpeed() == firstGearMaxSpeed);
	REQUIRE_THROWS_AS(car.SetGear(-1), UncorrectGearshiftException);

	REQUIRE_THROWS_AS(car.SetSpeed(firstGearMaxSpeed + 1), SpeedOutOfGearRangeException);
	REQUIRE_THROWS_AS(car.SetSpeed(firstGearMinSpeed - 1), NegativeSpeedException);

	// second Gear
	car.SetGear(2);
	REQUIRE(car.GetSpeed() == firstGearMaxSpeed);
	REQUIRE(car.GetGear() == 2);

	car.SetSpeed(secondGearMinSpeed);
	REQUIRE(car.GetSpeed() == secondGearMinSpeed);
	REQUIRE_THROWS_AS(car.SetGear(3), UnsuitableCurrentSpeedException);
	REQUIRE_THROWS_AS(car.SetGear(-1), UncorrectGearshiftException);

	car.SetSpeed(secondGearMaxSpeed);
	REQUIRE(car.GetSpeed() == secondGearMaxSpeed);
	REQUIRE_THROWS_AS(car.SetGear(1), UnsuitableCurrentSpeedException);

	REQUIRE_THROWS_AS(car.SetSpeed(secondGearMaxSpeed + 1), SpeedOutOfGearRangeException);
	REQUIRE_THROWS_AS(car.SetSpeed(secondGearMinSpeed - 1), SpeedOutOfGearRangeException);

	// third Gear
	car.SetGear(3);
	REQUIRE(car.GetSpeed() == secondGearMaxSpeed);
	REQUIRE(car.GetGear() == 3);

	car.SetSpeed(thirdGearMinSpeed);
	REQUIRE(car.GetSpeed() == thirdGearMinSpeed);
	REQUIRE_THROWS_AS(car.SetGear(4), UnsuitableCurrentSpeedException);
	REQUIRE_THROWS_AS(car.SetGear(-1), UncorrectGearshiftException);

	car.SetSpeed(thirdGearMaxSpeed);
	REQUIRE(car.GetSpeed() == thirdGearMaxSpeed);
	REQUIRE_THROWS_AS(car.SetGear(2), UnsuitableCurrentSpeedException);

	REQUIRE_THROWS_AS(car.SetSpeed(thirdGearMaxSpeed + 1), SpeedOutOfGearRangeException);
	REQUIRE_THROWS_AS(car.SetSpeed(thirdGearMinSpeed - 1), SpeedOutOfGearRangeException);

	// fourth Gear
	car.SetGear(4);
	REQUIRE(car.GetSpeed() == thirdGearMaxSpeed);
	REQUIRE(car.GetGear() == 4);

	car.SetSpeed(fourthGearMinSpeed);
	REQUIRE(car.GetSpeed() == fourthGearMinSpeed);
	REQUIRE_THROWS_AS(car.SetGear(5), UnsuitableCurrentSpeedException);
	REQUIRE_THROWS_AS(car.SetGear(-1), UncorrectGearshiftException);

	car.SetSpeed(fourthGearMaxSpeed);
	REQUIRE(car.GetSpeed() == fourthGearMaxSpeed);
	REQUIRE_THROWS_AS(car.SetGear(3), UnsuitableCurrentSpeedException);

	REQUIRE_THROWS_AS(car.SetSpeed(fourthGearMaxSpeed + 1), SpeedOutOfGearRangeException);
	REQUIRE_THROWS_AS(car.SetSpeed(fourthGearMinSpeed - 1), SpeedOutOfGearRangeException);

	// fifth Gear
	car.SetGear(5);
	REQUIRE(car.GetSpeed() == fourthGearMaxSpeed);
	REQUIRE(car.GetGear() == 5);

	car.SetSpeed(fifthGearMinSpeed);
	REQUIRE(car.GetSpeed() == fifthGearMinSpeed);
	REQUIRE_THROWS_AS(car.SetGear(6), InvalidGearException);
	REQUIRE_THROWS_AS(car.SetGear(-1), UncorrectGearshiftException);

	car.SetSpeed(fifthGearMaxSpeed);
	REQUIRE(car.GetSpeed() == fifthGearMaxSpeed);
	REQUIRE_THROWS_AS(car.SetGear(4), UnsuitableCurrentSpeedException);

	REQUIRE_THROWS_AS(car.SetSpeed(fifthGearMaxSpeed + 1), SpeedOutOfGearRangeException);
	REQUIRE_THROWS_AS(car.SetSpeed(fifthGearMinSpeed - 1), SpeedOutOfGearRangeException);
}

TEST_CASE("TestSetGearAndSetSpeedSuccess")
{
	Transmission transmission = CreateTransmission();
	Car car(transmission);
	car.TurnOnEngine();

	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);

	car.SetGear(-1);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == -1);

	car.SetSpeed(20);
	REQUIRE(car.GetDirection() == Direction::BACKWARD);
	REQUIRE(car.GetSpeed() == 20);
	REQUIRE(car.GetGear() == -1);

	car.SetGear(0);
	REQUIRE(car.GetDirection() == Direction::BACKWARD);
	REQUIRE(car.GetSpeed() == 20);
	REQUIRE(car.GetGear() == 0);

	car.SetSpeed(0);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);

	car.SetGear(1);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 1);

	car.SetSpeed(20);
	REQUIRE(car.GetDirection() == Direction::FORWARD);
	REQUIRE(car.GetSpeed() == 20);
	REQUIRE(car.GetGear() == 1);

	car.SetGear(2);
	REQUIRE(car.GetDirection() == Direction::FORWARD);
	REQUIRE(car.GetSpeed() == 20);
	REQUIRE(car.GetGear() == 2);

	car.SetSpeed(50);
	REQUIRE(car.GetDirection() == Direction::FORWARD);
	REQUIRE(car.GetSpeed() == 50);
	REQUIRE(car.GetGear() == 2);

	car.SetGear(0);
	REQUIRE(car.GetDirection() == Direction::FORWARD);
	REQUIRE(car.GetSpeed() == 50);
	REQUIRE(car.GetGear() == 0);

	car.SetSpeed(0);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);
}

TEST_CASE("TestCarTurnOffEngineFailed")
{
	Transmission transmission = CreateTransmission();
	Car car(transmission);
	car.TurnOnEngine();
	car.SetGear(1);
	REQUIRE(car.GetEngineStatus() == true);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 1);
	REQUIRE_THROWS_AS(car.TurnOffEngine(), UncorrectTurnOffEngineException);

	car.SetGear(-1);
	REQUIRE(car.GetEngineStatus() == true);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == -1);
	REQUIRE_THROWS_AS(car.TurnOffEngine(), UncorrectTurnOffEngineException);

	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(0);
	REQUIRE(car.GetEngineStatus() == true);
	REQUIRE(car.GetDirection() == Direction::FORWARD);
	REQUIRE(car.GetSpeed() == 20);
	REQUIRE(car.GetGear() == 0);
	REQUIRE_THROWS_AS(car.TurnOffEngine(), UncorrectTurnOffEngineException);

	car.SetSpeed(0);
	car.SetGear(-1);
	car.SetSpeed(20);
	car.SetGear(0);
	REQUIRE(car.GetEngineStatus() == true);
	REQUIRE(car.GetDirection() == Direction::BACKWARD);
	REQUIRE(car.GetSpeed() == 20);
	REQUIRE(car.GetGear() == 0);
	REQUIRE_THROWS_AS(car.TurnOffEngine(), UncorrectTurnOffEngineException);
}

TEST_CASE("TestCarEngineOffGearSettingFailed")
{
	Transmission transmission = CreateTransmission();
	Car car(transmission);
	REQUIRE(car.GetEngineStatus() == false);
	REQUIRE_THROWS_AS(car.SetGear(-1), EngineOffGearSettingException);
	REQUIRE_THROWS_AS(car.SetGear(1), EngineOffGearSettingException);
	REQUIRE_THROWS_AS(car.SetGear(2), EngineOffGearSettingException);
}

TEST_CASE("TestCarEngineOffSpeedSettingFailed")
{
	Transmission transmission = CreateTransmission();
	Car car(transmission);
	REQUIRE(car.GetEngineStatus() == false);
	REQUIRE_THROWS_AS(car.SetSpeed(10), EngineOffSpeedSettingException);
	REQUIRE_THROWS_AS(car.SetSpeed(20), EngineOffSpeedSettingException);
	REQUIRE_THROWS_AS(car.SetSpeed(0), EngineOffSpeedSettingException);
}

TEST_CASE("TestCarNeutralGearAccelerationFailed")
{
	Transmission transmission = CreateTransmission();
	Car car(transmission);
	car.TurnOnEngine();
	REQUIRE(car.GetEngineStatus() == true);
	REQUIRE(car.GetGear() == 0);

	REQUIRE_THROWS_AS(car.SetSpeed(10), NeutralGearAccelerationException);

	car.SetSpeed(0);
	REQUIRE(car.GetSpeed() == 0);
}

TEST_CASE("TestCarSetNegativeSpeedFailed")
{
	Transmission transmission = CreateTransmission();
	Car car(transmission);
	car.TurnOnEngine();

	car.SetGear(1);
	REQUIRE(car.GetEngineStatus() == true);
	REQUIRE(car.GetGear() == 1);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
	REQUIRE_THROWS_AS(car.SetSpeed(-1), NegativeSpeedException);

	car.SetGear(-1);
	REQUIRE(car.GetGear() == -1);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
	REQUIRE_THROWS_AS(car.SetSpeed(-1), NegativeSpeedException);

	car.SetSpeed(10);
	REQUIRE(car.GetGear() == -1);
	REQUIRE(car.GetDirection() == Direction::BACKWARD);

	car.SetSpeed(0);
	car.SetGear(1);
	car.SetSpeed(10);
	REQUIRE(car.GetGear() == 1);
	REQUIRE(car.GetDirection() == Direction::FORWARD);
	REQUIRE_THROWS_AS(car.SetSpeed(-1), NegativeSpeedException);
}

TEST_CASE("TestCarSetSpeedOutOfGearRangeFailed")
{
	Transmission transmission = CreateTransmission();
	Car car(transmission);
	car.TurnOnEngine();

	car.SetGear(1);
	REQUIRE(car.GetGear() == 1);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
	REQUIRE_THROWS_AS(car.SetSpeed(MAX_SPEED_FIRST_GEAR + 1), SpeedOutOfGearRangeException);

	car.SetSpeed(MIN_SPEED_SECOND_GEAR);
	car.SetGear(2);
	REQUIRE(car.GetGear() == 2);
	REQUIRE(car.GetDirection() == Direction::FORWARD);

	REQUIRE_THROWS_AS(car.SetSpeed(MAX_SPEED_SECOND_GEAR + 1), SpeedOutOfGearRangeException);
	REQUIRE_THROWS_AS(car.SetSpeed(MIN_SPEED_SECOND_GEAR - 1), SpeedOutOfGearRangeException);

	car.SetGear(0);
	car.SetSpeed(0);
	car.SetGear(-1);
	REQUIRE(car.GetGear() == -1);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
	REQUIRE_THROWS_AS(car.SetSpeed(MAX_SPEED_REVERSE_GEAR + 1), SpeedOutOfGearRangeException);
}
