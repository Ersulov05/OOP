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

TEST_CASE("TestProcessCarCommand")
{
	std::stringstream output;

	Car car = CreateCar();
	CarController carController(car);
	REQUIRE(carController.GetCar().GetEngineStatus() == false);

	carController.ProcessCarCommand(output, CarCommand::ENGINE_ON, {});
	REQUIRE(carController.GetCar().GetEngineStatus() == true);

	carController.ProcessCarCommand(output, CarCommand::SET_GEAR, { "1" });
	REQUIRE(carController.GetCar().GetGear() == 1);

	carController.ProcessCarCommand(output, CarCommand::SET_SPEED, { "20" });
	REQUIRE(carController.GetCar().GetSpeed() == 20);

	carController.ProcessCarCommand(output, CarCommand::SET_GEAR, { "0" });
	REQUIRE(carController.GetCar().GetGear() == 0);

	carController.ProcessCarCommand(output, CarCommand::SET_SPEED, { "0" });
	REQUIRE(carController.GetCar().GetSpeed() == 0);

	carController.ProcessCarCommand(output, CarCommand::ENGINE_OFF, {});
	REQUIRE(carController.GetCar().GetEngineStatus() == false);

	carController.ProcessCarCommand(output, CarCommand::UNKNOWN, {});
	REQUIRE(output.str() == "Unknown command\n");
}