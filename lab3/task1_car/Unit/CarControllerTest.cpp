#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Controller/CarController.h"
#include <sstream>

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

TEST_CASE("TestProcessCarCommand")
{
	std::stringstream output;
	Transmission transmission = CreateTransmission();
	Car car(transmission);
	CarController carController(car);
	REQUIRE(carController.GetCar().GetEngineStatus() == false);

	carController.HandleCarCommand(output, CarCommand::ENGINE_ON, {});
	REQUIRE(carController.GetCar().GetEngineStatus() == true);

	carController.HandleCarCommand(output, CarCommand::SET_GEAR, { "1" });
	REQUIRE(carController.GetCar().GetGear() == 1);

	carController.HandleCarCommand(output, CarCommand::SET_SPEED, { "20" });
	REQUIRE(carController.GetCar().GetSpeed() == 20);

	carController.HandleCarCommand(output, CarCommand::SET_GEAR, { "0" });
	REQUIRE(carController.GetCar().GetGear() == 0);

	carController.HandleCarCommand(output, CarCommand::SET_SPEED, { "0" });
	REQUIRE(carController.GetCar().GetSpeed() == 0);

	carController.HandleCarCommand(output, CarCommand::ENGINE_OFF, {});
	REQUIRE(carController.GetCar().GetEngineStatus() == false);

	carController.HandleCarCommand(output, CarCommand::UNKNOWN, {});
	REQUIRE(output.str() == "Unknown command\n");
}