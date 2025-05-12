#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../src/CMyString.h"
#include <sstream>

TEST_CASE("TestCreateStringSuccess")
{
	CMyString string;

	REQUIRE(string.GetLength() == 0);
	REQUIRE(string.GetCapacity() == 1);

	string = "999";
	REQUIRE(string.GetLength() == 3);
	REQUIRE(string.GetCapacity() == 4);

	std::string str = "string";
	string = str;
	REQUIRE(string.GetLength() == 6);
	REQUIRE(string.GetCapacity() == 7);

	CMyString copyString = string;
	REQUIRE(string.GetLength() == 6);
	REQUIRE(string.GetCapacity() == 7);
	REQUIRE(copyString.GetLength() == 6);
	REQUIRE(copyString.GetCapacity() == 7);

	CMyString moveString = std::move(string);
	REQUIRE(moveString.GetLength() == 6);
	REQUIRE(moveString.GetCapacity() == 7);
	REQUIRE(string.GetLength() == 0);
	REQUIRE(string.GetCapacity() == 1);
}

TEST_CASE("TestCMyStringComparisonOperationsSuccess")
{
	CMyString firstString = "111";
	CMyString secondString = "222";
	REQUIRE(firstString == "111");
	REQUIRE(secondString == "222");
	REQUIRE(firstString < secondString);
	REQUIRE(firstString <= secondString);
	REQUIRE(firstString != secondString);
	REQUIRE_FALSE(firstString > secondString);
	REQUIRE_FALSE(firstString >= secondString);
	REQUIRE_FALSE(firstString == secondString);

	firstString = secondString;
	REQUIRE(firstString == secondString);
	REQUIRE(firstString >= secondString);
	REQUIRE(firstString <= secondString);
	REQUIRE_FALSE(firstString < secondString);
	REQUIRE_FALSE(secondString < firstString);
	REQUIRE_FALSE(firstString != secondString);
}

TEST_CASE("TestCMyStringPlusOperationsSuccess")
{
	CMyString firstString = "111";
	CMyString secondString = "222";
	CMyString emptyString;
	std::string str = "000";
	REQUIRE(firstString + secondString == "111222");
	REQUIRE(secondString + firstString == "222111");
	REQUIRE(firstString + emptyString == "111");
	REQUIRE(emptyString + firstString == "111");
	REQUIRE("999" + firstString == "999111");
	REQUIRE(firstString + "999" == "111999");
	REQUIRE(str + firstString == "000111");
	REQUIRE(firstString + str == "111000");

	firstString += secondString;
	REQUIRE(firstString == "111222");

	firstString += emptyString;
	REQUIRE(firstString == "111222");

	firstString += "999";
	REQUIRE(firstString == "111222999");

	firstString += str;
	REQUIRE(firstString == "111222999000");
}
