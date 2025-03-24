#pragma once
#include "../Car/Car.h"
#include "CarCommand.h"
#include <iostream>
#include <string>
#include <vector>

class CarController
{
public:
	// TODO: Добавить explicit везде
	explicit CarController(Car& car);
	// TODO: Process -> Handle
	void HandleCarCommand(std::ostream& output, CarCommand command, const std::vector<std::string>& stringArgs);
	[[nodiscard]] Car GetCar() const;

private:
	void ExecuteCarCommand(std::ostream& output, CarCommand command, const std::vector<std::string>& stringArgs);
	void PrintCarInfo(std::ostream& output);
	void SetCarSpeed(const std::vector<std::string>& stringArgs);
	void SetCarGear(const std::vector<std::string>& stringArgs);
	Car m_car; // TODO Либо создавать машину тут либо передавать по ссылке или по поинтеру
};