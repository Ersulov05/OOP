#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../src/CStringList.h"
#include "../src/Exception/EraseEndIteratorException.h"
#include "../src/Exception/IndexOutOfRangeException.h"
#include <sstream>

TEST_CASE("TestCreateStringListSuccess")
{
	CStringList stringList;

	REQUIRE(stringList.Size() == 0);
	REQUIRE(stringList.IsEmpty());
}

TEST_CASE("TestStringListBegin")
{
	CStringList stringList;

	auto begin = stringList.begin();
	REQUIRE(begin.GetNode()->data == "");

	stringList.PushBack("str");
	begin = stringList.begin();
	REQUIRE(begin.GetNode()->data == "str");

	stringList.PushBack("1");
	begin = stringList.begin();
	REQUIRE(begin.GetNode()->data == "str");

	stringList.PushFront("2");
	begin = stringList.begin();
	REQUIRE(begin.GetNode()->data == "2");
}

TEST_CASE("TestStringListEnd")
{
	CStringList stringList;

	auto end = stringList.end();
	REQUIRE(end.GetNode()->data == "");

	stringList.PushBack("str");
	end = stringList.end();
	REQUIRE(end.GetNode()->data == "");

	stringList.PushFront("2");
	end = stringList.end();
	REQUIRE(end.GetNode()->data == "");
}

TEST_CASE("TestStringListPushBack")
{
	CStringList stringList;

	stringList.PushBack("hello");
	REQUIRE(stringList.Size() == 1);
	REQUIRE(stringList[0] == "hello");

	stringList.PushBack("world");
	REQUIRE(stringList.Size() == 2);
	REQUIRE(stringList[1] == "world");

	stringList.PushBack("!");
	REQUIRE(stringList.Size() == 3);
	REQUIRE(stringList[2] == "!");
}

TEST_CASE("TestStringListPushFront")
{
	CStringList stringList;

	stringList.PushFront("hello");
	REQUIRE(stringList.Size() == 1);
	REQUIRE(stringList[0] == "hello");

	stringList.PushFront("world");
	REQUIRE(stringList.Size() == 2);
	REQUIRE(stringList[1] == "hello");
	REQUIRE(stringList[0] == "world");

	stringList.PushFront("!");
	REQUIRE(stringList.Size() == 3);
	REQUIRE(stringList[2] == "hello");
	REQUIRE(stringList[0] == "!");
}

TEST_CASE("TestStringListInsert")
{
	CStringList stringList;

	stringList.Insert(stringList.begin(), "hello");
	REQUIRE(stringList.Size() == 1);
	REQUIRE(stringList[0] == "hello");

	stringList.Insert(stringList.begin() + 1, "world");
	REQUIRE(stringList.Size() == 2);
	REQUIRE(stringList[1] == "world");

	stringList.Insert(stringList.end(), "!");
	REQUIRE(stringList.Size() == 3);
	REQUIRE(stringList[2] == "!");
}

TEST_CASE("TestStringListErase")
{
	CStringList stringList;

	stringList.PushBack("hello");
	stringList.PushBack("world");
	stringList.PushBack("!");
	REQUIRE(stringList.Size() == 3);
	REQUIRE(stringList[0] == "hello");
	REQUIRE(stringList[2] == "!");

	stringList.Erase(stringList.begin());
	REQUIRE(stringList.Size() == 2);
	REQUIRE(stringList[0] == "world");
	REQUIRE(stringList[1] == "!");

	stringList.Erase(stringList.end() - 1);
	REQUIRE(stringList.Size() == 1);
	REQUIRE(stringList[0] == "world");

	stringList.Erase(stringList.end() - 1);
	REQUIRE(stringList.Size() == 0);
}

TEST_CASE("TestStringListClear")
{
	CStringList stringList;

	stringList.Clear();
	REQUIRE(stringList.Size() == 0);
	REQUIRE(stringList.begin() == stringList.end());
	REQUIRE(*stringList.end() == "");

	stringList.PushBack("str");
	REQUIRE(stringList.Size() == 1);

	stringList.Clear();
	REQUIRE(stringList.Size() == 0);
	REQUIRE(stringList.begin() == stringList.end());
	REQUIRE(*stringList.end() == "");
}

TEST_CASE("TestStringListEraseFailed")
{
	CStringList stringList;

	REQUIRE_THROWS_AS(stringList.Erase(stringList.end()), EraseEndIteratorException);
	REQUIRE_THROWS_AS(stringList.Erase(stringList.begin()), EraseEndIteratorException);
	REQUIRE_THROWS_AS(stringList.Erase(stringList.rend()), EraseEndIteratorException);

	stringList.PushFront("hello");
	REQUIRE_THROWS_AS(stringList.Erase(stringList.end()), EraseEndIteratorException);
	REQUIRE_THROWS_AS(stringList.Erase(stringList.rend()), EraseEndIteratorException);
}

TEST_CASE("TestStringListIndexesAccess")
{
	CStringList stringList;

	stringList.PushBack("1");
	REQUIRE(stringList[0] == "1");

	stringList[0] = "2";
	REQUIRE(stringList[0] == "2");
}

TEST_CASE("TestStringListIndexesAccessFailed")
{
	CStringList stringList;
	REQUIRE_THROWS_AS(stringList[0], IndexOutOfRangeException);

	stringList.PushBack("1");
	REQUIRE_THROWS_AS(stringList[1], IndexOutOfRangeException);
}

TEST_CASE("TestCreateStringListByCopySuccess")
{
	CStringList stringList;
	stringList.PushBack("str");

	CStringList copyStringList(stringList);

	REQUIRE(stringList.Size() == copyStringList.Size());
	REQUIRE(stringList[0] == copyStringList[0]);
}

TEST_CASE("TestCreateStringListByMove")
{
	CStringList stringList;
	stringList.PushBack("str");
	REQUIRE(stringList.Size() == 1);

	CStringList moveStringList(std::move(stringList));

	REQUIRE(stringList.Size() == 0);
	REQUIRE(moveStringList.Size() == 1);
	REQUIRE(moveStringList[0] == "str");
}

TEST_CASE("TestStringListCopyOperator")
{
	CStringList stringList;
	stringList.PushBack("str");

	CStringList copyStringList = stringList;

	REQUIRE(stringList.Size() == copyStringList.Size());
	REQUIRE(stringList[0] == copyStringList[0]);
}

TEST_CASE("TestStringListMoveOperator")
{
	CStringList stringList;

	stringList.PushBack("str");
	REQUIRE(stringList.Size() == 1);

	CStringList moveStringList = std::move(stringList);

	REQUIRE(stringList.Size() == 0);
	REQUIRE(moveStringList.Size() == 1);
	REQUIRE(moveStringList[0] == "str");
}

TEST_CASE("TestRangeFor")
{
	CStringList stringList;
	stringList.PushBack("hello");
	stringList.PushBack("world");
	stringList.PushBack("!");
	stringList.PushBack("goodbie");

	std::vector<std::string> stringVector;
	for (const auto& string : stringList)
	{
		stringVector.push_back(string);
	}
	REQUIRE(stringVector == std::vector<std::string>({ "hello", "world", "!", "goodbie" }));

	stringVector.clear();
	for (auto it = stringList.begin(); it != stringList.end(); ++it)
	{
		stringVector.push_back(*it);
	}
	REQUIRE(stringVector == std::vector<std::string>({ "hello", "world", "!", "goodbie" }));
}

TEST_CASE("TestReverseFor")
{
	CStringList stringList;
	stringList.PushBack("hello");
	stringList.PushBack("world");
	stringList.PushBack("!");
	stringList.PushBack("goodbie");

	std::vector<std::string> reversedVector;
	for (auto it = stringList.rbegin(); it != stringList.rend(); ++it)
	{
		reversedVector.push_back(*it);
	}
	REQUIRE(reversedVector == std::vector<std::string>({ "goodbie", "!", "world", "hello" }));
}