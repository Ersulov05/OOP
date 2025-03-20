#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Controller/CarCommand.h"
#include <string>

TEST_CASE("TestGetCarCommandByString")
{
	std::string stringCommand;
	REQUIRE(GetCarCommandByString(stringCommand) == CarCommand::UNKNOWN);

	stringCommand = "hello";
	REQUIRE(GetCarCommandByString(stringCommand) == CarCommand::UNKNOWN);

	stringCommand = "Info";
	REQUIRE(GetCarCommandByString(stringCommand) == CarCommand::INFO);

	stringCommand = "info";
	REQUIRE(GetCarCommandByString(stringCommand) == CarCommand::UNKNOWN);

	stringCommand = "EngineOn";
	REQUIRE(GetCarCommandByString(stringCommand) == CarCommand::ENGINE_ON);

	stringCommand = "EngineOff";
	REQUIRE(GetCarCommandByString(stringCommand) == CarCommand::ENGINE_OFF);

	stringCommand = "SetGear";
	REQUIRE(GetCarCommandByString(stringCommand) == CarCommand::SET_GEAR);

	stringCommand = "SetSpeed";
	REQUIRE(GetCarCommandByString(stringCommand) == CarCommand::SET_SPEED);
}