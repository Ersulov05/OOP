#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../src/CMyString.h"
#include "../src/Exception/IndexOutOfRangeException.h"
#include <sstream>

TEST_CASE("TestCreateStringSuccess") // TODO Разделить по тесту на каждый конструктор
{
	CMyString string;

	REQUIRE(string.GetLength() == 0);
	REQUIRE(string.GetCapacity() == 1);
}

TEST_CASE("TestCreateStringByCharString")
{
	CMyString string = "999";

	REQUIRE(string.GetLength() == 3);
	REQUIRE(string.GetCapacity() == 4);
}

TEST_CASE("TestCreateStringByStlString")
{
	CMyString string;
	std::string str = "string";
	string = str;

	REQUIRE(string.GetLength() == 6);
	REQUIRE(string.GetCapacity() == 7);
}

TEST_CASE("TestCopyString")
{
	CMyString string = "string";
	CMyString copyString = string;

	REQUIRE(string.GetLength() == 6);
	REQUIRE(string.GetCapacity() == 7);
	REQUIRE(copyString.GetLength() == 6);
	REQUIRE(copyString.GetCapacity() == 7);
}

TEST_CASE("TestMoveCMyString")
{
	CMyString string = "xxx";
	CMyString str = std::move(string);

	REQUIRE(string.GetCapacity() == 1);
	REQUIRE(string.GetLength() == 0);
	REQUIRE(string == "");
	REQUIRE(str.GetLength() == 3);
	REQUIRE(str.GetCapacity() == 4);
	REQUIRE(str == "xxx");
}

TEST_CASE("TestMoveEmptyCMyString")
{
	CMyString emptyString;
	CMyString str = std::move(emptyString);

	REQUIRE(emptyString.GetCapacity() == 1);
	REQUIRE(emptyString.GetLength() == 0);
	REQUIRE(emptyString == "");
	REQUIRE(str.GetLength() == 0);
	REQUIRE(str.GetCapacity() == 1);
	REQUIRE(str == "");
}

TEST_CASE("TestCMyStringEqualsOperation") // TODO: Разделить
{
	CMyString firstString = "111";
	CMyString equalsString = "111";
	CMyString notEqualsString = "222";

	REQUIRE(firstString == "111");
	REQUIRE(firstString == equalsString);
	REQUIRE_FALSE(firstString == notEqualsString);
}

TEST_CASE("TestCMyStringNotEqualsOperation")
{
	CMyString firstString = "111";
	CMyString equalsString = "111";
	CMyString notEqualsString = "222";

	REQUIRE(firstString != "222");
	REQUIRE(firstString != notEqualsString);
	REQUIRE_FALSE(firstString != equalsString);
}

TEST_CASE("TestCMyStringLessOperation")
{
	CMyString string = "111";

	REQUIRE(string < "222");
	REQUIRE(string < "2");
	REQUIRE(string < "1111");
	REQUIRE_FALSE(string < "00000");
	REQUIRE_FALSE(string < "111");
	REQUIRE_FALSE(string < "1");
}

TEST_CASE("TestCMyStringGreetOperation")
{
	CMyString string = "111";

	REQUIRE_FALSE(string > "222");
	REQUIRE_FALSE(string > "2");
	REQUIRE_FALSE(string > "1111");
	REQUIRE_FALSE(string > "111");
	REQUIRE(string > "00000");
	REQUIRE(string > "0");
	REQUIRE(string > "1");
}

TEST_CASE("TestCMyStringLessEqualsOperations")
{
	CMyString string = "111";

	REQUIRE(string <= "222");
	REQUIRE(string <= "2");
	REQUIRE(string <= "1111");
	REQUIRE(string <= "111");
	REQUIRE_FALSE(string <= "00000");
	REQUIRE_FALSE(string <= "1");
}

TEST_CASE("TestCMyStringGreatEqualsOperations")
{
	CMyString string = "111";

	REQUIRE_FALSE(string >= "222");
	REQUIRE_FALSE(string >= "2");
	REQUIRE_FALSE(string >= "1111");
	REQUIRE(string >= "111");
	REQUIRE(string >= "00000");
	REQUIRE(string >= "0");
	REQUIRE(string >= "1");
}

TEST_CASE("TestCMyStringPlusOperation")
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
}

TEST_CASE("TestCMyStringPlusEqualsOperation")
{
	CMyString firstString = "111";
	CMyString secondString = "222";
	CMyString emptyString;
	std::string str = "000";

	firstString += secondString;
	REQUIRE(firstString == "111222");

	firstString += emptyString;
	REQUIRE(firstString == "111222");

	firstString += "999";
	REQUIRE(firstString == "111222999");

	firstString += str;
	REQUIRE(firstString == "111222999000");
}

TEST_CASE("TestCMyStringGetSymbolByIndex")
{
	CMyString string = "12345";
	const CMyString constString = "12345";

	REQUIRE(string[0] == '1');
	REQUIRE(string[1] == '2');
	REQUIRE(constString[0] == '1');
	REQUIRE(constString[1] == '2');
	char x = string[1];
	x = '8';
	REQUIRE(string[1] == '2');
}

TEST_CASE("TestCMyStringChangeSymbolByIndex")
{
	CMyString string = "12345";

	string[0] = '0';
	REQUIRE(string[0] == '0');
	REQUIRE(string[1] == '2');
}

TEST_CASE("TestCMyStringGetAndChangeSumbolFailed")
{
	CMyString string = "12345";
	const CMyString constString = "12345";
	CMyString emptyString;

	REQUIRE_THROWS_AS(emptyString[0], IndexOutOfRangeException);
	REQUIRE_THROWS_AS(emptyString[-1], IndexOutOfRangeException);
	REQUIRE_THROWS_AS(emptyString[1], IndexOutOfRangeException);

	REQUIRE_THROWS_AS(string[-1], IndexOutOfRangeException);
	REQUIRE_THROWS_AS(string[string.GetLength()], IndexOutOfRangeException);
	REQUIRE_THROWS_AS(emptyString[0] = '7', IndexOutOfRangeException);
	REQUIRE_THROWS_AS(string[string.GetLength()] = '7', IndexOutOfRangeException);

	REQUIRE_THROWS_AS(constString[constString.GetLength()], IndexOutOfRangeException);
	REQUIRE_THROWS_AS(constString[-1], IndexOutOfRangeException);
}

TEST_CASE("TestCMyStringSubStringSuccess")
{
	CMyString string = "12345";
	const CMyString constString = "12345";
	CMyString emptyString;

	REQUIRE(string.SubString(0) == "12345");
	REQUIRE(constString.SubString(0) == "12345");

	REQUIRE(string.SubString(0, 0) == "");
	REQUIRE(emptyString.SubString(0) == "");

	REQUIRE(string.SubString(0, 3) == "123");
	REQUIRE(constString.SubString(0, 3) == "123");

	REQUIRE(string.SubString(0, string.GetLength()) == "12345");
	REQUIRE(constString.SubString(0, constString.GetLength()) == "12345");
}

TEST_CASE("TestInputCMyString")
{
	std::stringstream input;
	CMyString string;

	input >> string;
	REQUIRE(string == "");

	input.clear();
	input.str("hello");
	input >> string;
	REQUIRE(string == "hello");

	input.clear();
	input.str("hello     world !\ngoodbie");
	input >> string;
	REQUIRE(string == "hello");
	input >> string;
	REQUIRE(string == "world");
	input >> string;
	REQUIRE(string == "!");
	input >> string;
	REQUIRE(string == "goodbie");
	input >> string;
	REQUIRE(string == "");
}

TEST_CASE("TestOutputCMyString")
{
	std::stringstream output;
	CMyString string;

	output << string;
	REQUIRE(output.str() == "");

	string = "xyz";
	output << string;
	REQUIRE(output.str() == "xyz");
	output.str("");

	string = "hello world";
	output << string;
	REQUIRE(output.str() == "hello world");
	output.str("");

	string = "hello \n world";
	output << string;
	REQUIRE(output.str() == "hello \n world");
	output.str("");

	string = "xyz\0xyz";
	output << string;
	REQUIRE(output.str() == "xyz\0xyz");
	output.str("");

	string = "   \n\nxxy ";
	output << string;
	REQUIRE(output.str() == "   \n\nxxy ");
}

TEST_CASE("TestStlFunctions")
{
	CMyString str = "Hello";
	std::reverse(str.begin(), str.end());
	REQUIRE(str == "olleH");

	*str.begin() = 'X';
	*(str.end() - 1) = 'Y';
	REQUIRE(str == "XlleY");

	auto beginIt = str.begin();
	REQUIRE(*(++beginIt) == 'l');
	REQUIRE(*(--beginIt) == 'X');

	auto endIt = str.end();
	REQUIRE(*(--endIt) == 'Y');
	REQUIRE(*(++endIt) == '\0');

	CMyString emptyString;
	REQUIRE(emptyString.begin() == emptyString.end());
}

TEST_CASE("TestRangeFor")
{
	CMyString str = CMyString("123");
	std::string string;
	for (const auto& ch : str)
	{
		string += ch;
	}
	REQUIRE(string == "123");

	string = "";
	for (auto it = str.begin(); it != str.end(); ++it)
	{
		string += *it;
	}
	REQUIRE(string == "123");

	std::string reversed;
	for (auto it = str.rbegin(); it != str.rend(); ++it)
	{
		reversed += *it;
	}
	REQUIRE(reversed == "321");
}

TEST_CASE("TestReverseFor")
{
	CMyString str = CMyString("123");
	std::string string;

	std::string reversed;
	for (auto it = str.rbegin(); it != str.rend(); ++it)
	{
		reversed += *it;
	}
	REQUIRE(reversed == "321");
}
