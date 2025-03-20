#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../AppCommand.h"
#include <sstream>

TEST_CASE("TestGetAppCommand")
{
	std::stringstream input;

	input.str("hello as 23");
	AppCommand appCommand = GetAppCommand(input);
	REQUIRE(appCommand.stringCommand == "hello");
	REQUIRE(appCommand.stringArgs == std::vector<std::string>{ "as", "23" });

	input.str("hello    ");
	input.clear();
	appCommand = GetAppCommand(input);
	REQUIRE(appCommand.stringCommand == "hello");
	REQUIRE(appCommand.stringArgs == std::vector<std::string>{});

	input.str("    ");
	input.clear();
	appCommand = GetAppCommand(input);
	REQUIRE(appCommand.stringCommand == "");
	REQUIRE(appCommand.stringArgs == std::vector<std::string>{});

	input.str("");
	input.clear();
	appCommand = GetAppCommand(input);
	REQUIRE(appCommand.stringCommand == "");
	REQUIRE(appCommand.stringArgs == std::vector<std::string>{});
}