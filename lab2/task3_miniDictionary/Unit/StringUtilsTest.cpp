#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Utils/StringUtils.h"

TEST_CASE("TestGetTrimmedString")
{
	REQUIRE(GetTrimmedString("  hello  ") == "hello");
	REQUIRE(GetTrimmedString(" ") == "");
	REQUIRE(GetTrimmedString("            ") == "");
	REQUIRE(GetTrimmedString("hello") == "hello");
}

TEST_CASE("TestGetLowerCase")
{
	setlocale(LC_ALL, "ru_RU.UTF-8");

	REQUIRE(GetLowerCase("HeLLo") == "hello");
	REQUIRE(GetLowerCase("HELLO") == "hello");
	REQUIRE(GetLowerCase("hello") == "hello");
	REQUIRE(GetLowerCase("кот") == "кот");
	REQUIRE(GetLowerCase("КоТ") == "кот");
	REQUIRE(GetLowerCase("") == "");
}

TEST_CASE("TestGetEscapedString")
{
	setlocale(LC_ALL, "ru_RU.UTF-8");

	REQUIRE(GetEscapedString("HeLLo", "L") == "He\\L\\Lo");
	REQUIRE(GetEscapedString("HeL\\Lo", "L") == "He\\L\\\\Lo");
	REQUIRE(GetEscapedString("", "L") == "");
}

TEST_CASE("TestGetUnescapedString")
{
	setlocale(LC_ALL, "ru_RU.UTF-8");

	REQUIRE(GetUnescapedString("HeLLo", "L") == "HeLLo");
	REQUIRE(GetUnescapedString("HeL\\Lo", "L") == "HeLLo");
	REQUIRE(GetUnescapedString("He\\L\\\\Lo", "L") == "HeL\\Lo");
	REQUIRE(GetUnescapedString("", "L") == "");
}