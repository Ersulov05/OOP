#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Car/Car.h"
#include "../Car/Exception/EngineOffGearSettingException.h"
#include "../Car/Exception/EngineOffSpeedSettingException.h"
#include "../Car/Exception/NegativeSpeedException.h"
#include "../Car/Exception/NeutralGearAccelerationException.h"
#include "../Car/Exception/SpeedOutOfGearRangeException.h"
#include "../Car/Exception/UncorrectTurnOffEngineException.h"

const int MIN_SPEED_REVERSE_GEAR = 0;
const int MAX_SPEED_REVERSE_GEAR = 20;
const int MIN_SPEED_FIRST_GEAR = 0;
const int MAX_SPEED_FIRST_GEAR = 30;
const int MIN_SPEED_SECOND_GEAR = 20;
const int MAX_SPEED_SECOND_GEAR = 50;

Car CreateCar()
{
	GearSpeedInterval reverseGearSpeedInterval = { MIN_SPEED_REVERSE_GEAR, MAX_SPEED_REVERSE_GEAR };
	std::vector<GearSpeedInterval> driveGearSpeedIntervals = {
		{ MIN_SPEED_FIRST_GEAR, MAX_SPEED_FIRST_GEAR },
		{ MIN_SPEED_SECOND_GEAR, MAX_SPEED_SECOND_GEAR }
	};
	Transmission transmission(reverseGearSpeedInterval, driveGearSpeedIntervals);

	return Car(transmission);
}

TEST_CASE("TestCarTurnOnOffEngineSuccess")
{
	Car car = CreateCar();

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

TEST_CASE("TestSetGearAndSetSpeedSuccess")
{
	Car car = CreateCar();
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
	Car car = CreateCar();
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
	Car car = CreateCar();
	REQUIRE(car.GetEngineStatus() == false);
	REQUIRE_THROWS_AS(car.SetGear(-1), EngineOffGearSettingException);
	REQUIRE_THROWS_AS(car.SetGear(1), EngineOffGearSettingException);
	REQUIRE_THROWS_AS(car.SetGear(2), EngineOffGearSettingException);
}

TEST_CASE("TestCarEngineOffSpeedSettingFailed")
{
	Car car = CreateCar();
	REQUIRE(car.GetEngineStatus() == false);
	REQUIRE_THROWS_AS(car.SetSpeed(10), EngineOffSpeedSettingException);
	REQUIRE_THROWS_AS(car.SetSpeed(20), EngineOffSpeedSettingException);
	REQUIRE_THROWS_AS(car.SetSpeed(0), EngineOffSpeedSettingException);
}

TEST_CASE("TestCarNeutralGearAccelerationFailed")
{
	Car car = CreateCar();
	car.TurnOnEngine();
	REQUIRE(car.GetEngineStatus() == true);
	REQUIRE(car.GetGear() == 0);

	REQUIRE_THROWS_AS(car.SetSpeed(10), NeutralGearAccelerationException);

	car.SetSpeed(0);
	REQUIRE(car.GetSpeed() == 0);
}

TEST_CASE("TestCarSetNegativeSpeedFailed")
{
	Car car = CreateCar();
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
	Car car = CreateCar();
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
