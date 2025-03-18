#pragma once
#include "../Car/Car.h"
#include "CarCommand.h"
#include <iostream>
#include <string>
#include <vector>

class CarController
{
public:
	CarController(Car car);
	void ProcessCarCommand(std::ostream& output, CarCommand command, const std::vector<std::string>& stringArgs);

private:
	void ExecuteCarCommand(std::ostream& output, CarCommand command, const std::vector<std::string>& stringArgs);
	void PrintCarInfo(std::ostream& output);
	void SetCarSpeed(const std::vector<std::string>& stringArgs);
	void SetCarGear(const std::vector<std::string>& stringArgs);
	Car car;
};