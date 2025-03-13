// #include "./Car/Gear.h"
// #include "./Car/Transmission/Transmission.h"
#include "./Car/Car.h"
#include "./Controller/CarController.h"
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

struct Command
{
	std::string stringCommand;
	std::vector<std::string> stringArgs;
};

Command GetCommand(std::istream& input)
{
	std::string line;
	getline(input, line);

	std::istringstream lineStream(line);
	Command command;
	lineStream >> command.stringCommand;
	std::string arg;
	while (lineStream >> arg)
	{
		command.stringArgs.push_back(arg);
	}

	return command;
}

// Transmission CreateTransmission()
// {
// 	return Transmission({ 0, 20 }, { { 0, 20 }, { 10, 40 }, { 20, 80 } });
// }

Car CreateCar()
{
	Transmission transmission({ 0, 20 }, { { 0, 20 }, { 10, 40 }, { 20, 80 } });
	return Car(transmission);
}

void CarProcess(std::istream& input, std::ostream& output)
{
	Car car = CreateCar();
	std::string line;
	while (true)
	{
		Command appCommand = GetCommand(input);
		if (appCommand.stringCommand == "Exit")
		{
			break;
		}
		CarCommand carCommand = GetCarCommandByString(appCommand.stringCommand);
		ProcessCarCommand(output, car, carCommand, appCommand.stringArgs);
	}
}

int main(int argc, char* argv[])
{
	try
	{
		CarProcess(std::cin, std::cout);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}