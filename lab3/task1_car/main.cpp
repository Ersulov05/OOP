#include "./AppCommand.h"
#include "./Car/Car.h"
#include "./Controller/CarCommand.h"
#include "./Controller/CarController.h"
#include <iostream>

const std::string EXIT_STRING = "Exit";
const std::string BEGIN_STRING_INPUT = ">";
const int MIN_SPEED_REVERSE_GEAR = 0;
const int MAX_SPEED_REVERSE_GEAR = 20;
const int MIN_SPEED_FIRST_GEAR = 0;
const int MAX_SPEED_FIRST_GEAR = 30;
const int MIN_SPEED_SECOND_GEAR = 20;
const int MAX_SPEED_SECOND_GEAR = 50;
const int MIN_SPEED_THIRD_GEAR = 30;
const int MAX_SPEED_THIRD_GEAR = 60;
const int MIN_SPEED_FOURTH_GEAR = 40;
const int MAX_SPEED_FOURTH_GEAR = 90;
const int MIN_SPEED_FIFTH_GEAR = 50;
const int MAX_SPEED_FIFTH_GEAR = 150;

Transmission CreateTransmission()
{
	GearSpeedInterval reverseGearSpeedInterval = { MIN_SPEED_REVERSE_GEAR, MAX_SPEED_REVERSE_GEAR };
	std::vector<GearSpeedInterval> driveGearSpeedIntervals = {
		{ MIN_SPEED_FIRST_GEAR, MAX_SPEED_FIRST_GEAR },
		{ MIN_SPEED_SECOND_GEAR, MAX_SPEED_SECOND_GEAR },
		{ MIN_SPEED_THIRD_GEAR, MAX_SPEED_THIRD_GEAR },
		{ MIN_SPEED_FOURTH_GEAR, MAX_SPEED_FOURTH_GEAR },
		{ MIN_SPEED_FIFTH_GEAR, MAX_SPEED_FIFTH_GEAR }
	};
	return Transmission(reverseGearSpeedInterval, driveGearSpeedIntervals);
}

// TODO: Process -> Handle
void CarHandle(std::istream& input, std::ostream& output)
{
	Transmission transmission = CreateTransmission();
	Car car(transmission);
	CarController carController(car);
	std::string line;

	while (true)
	{
		output << BEGIN_STRING_INPUT;
		AppCommand appCommand = GetAppCommand(input);
		if (appCommand.stringCommand == EXIT_STRING)
		{
			break;
		}
		CarCommand carCommand = GetCarCommandByString(appCommand.stringCommand);
		carController.HandleCarCommand(output, carCommand, appCommand.stringArgs);
	}
}

int main(int argc, char* argv[])
{
	try
	{
		CarHandle(std::cin, std::cout);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}