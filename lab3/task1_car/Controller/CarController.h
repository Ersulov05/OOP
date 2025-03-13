#include "../Car/Car.h"
#include <iostream>
#include <string>
#include <vector>

enum class CarCommand
{
	ENGINE_ON,
	ENGINE_OFF,
	SET_GEAR,
	SET_SPEED,
	INFO,
	EXIT,
	UNKNOWN
};

CarCommand GetCarCommandByString(const std::string& string);

bool ProcessCarCommand(std::ostream& output, Car& car, CarCommand command, const std::vector<std::string>& stringArgs);