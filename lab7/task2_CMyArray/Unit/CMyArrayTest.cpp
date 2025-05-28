#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../src/CMyArray.h"
#include "../src/Exception/IndexOutOfRangeException.h"
#include <sstream>

TEST_CASE("TestCreateCMyArray")
{
	CMyArray<int> intArr;
	CMyArray<double> doubleArr;
	CMyArray<std::string> stringArr;

	REQUIRE(intArr.Size() == 0);
	REQUIRE(intArr.Capacity() == 0);

	REQUIRE(doubleArr.Size() == 0);
	REQUIRE(doubleArr.Capacity() == 0);

	REQUIRE(stringArr.Size() == 0);
	REQUIRE(stringArr.Capacity() == 0);
}

TEST_CASE("TestAddIntElementInCMyArray")
{
	CMyArray<int> arr;

	arr.Add(1);

	REQUIRE(arr.Size() == 1);
	REQUIRE(arr.Capacity() == 1);
	REQUIRE(arr[0] == 1);

	arr.Add(3);
	REQUIRE(arr.Size() == 2);
	REQUIRE(arr.Capacity() == 2);
	REQUIRE(arr[0] == 1);
	REQUIRE(arr[1] == 3);

	arr.Add(7);
	REQUIRE(arr.Size() == 3);
	REQUIRE(arr.Capacity() == 4);
	REQUIRE(arr[0] == 1);
	REQUIRE(arr[1] == 3);
	REQUIRE(arr[2] == 7);
}

TEST_CASE("TestAddDoubleElementInCMyArray")
{
	CMyArray<double> arr;

	arr.Add(1.5);

	REQUIRE(arr.Size() == 1);
	REQUIRE(arr.Capacity() == 1);
	REQUIRE(arr[0] == 1.5);

	arr.Add(3.89);
	REQUIRE(arr.Size() == 2);
	REQUIRE(arr.Capacity() == 2);
	REQUIRE(arr[0] == 1.5);
	REQUIRE(arr[1] == 3.89);

	arr.Add(-0.008);
	REQUIRE(arr.Size() == 3);
	REQUIRE(arr.Capacity() == 4);
	REQUIRE(arr[0] == 1.5);
	REQUIRE(arr[1] == 3.89);
	REQUIRE(arr[2] == -0.008);
}

TEST_CASE("TestAddStringElementInCMyArray")
{
	CMyArray<std::string> arr;

	arr.Add("hello");

	REQUIRE(arr.Size() == 1);
	REQUIRE(arr.Capacity() == 1);
	REQUIRE(arr[0] == "hello");

	arr.Add("world");
	REQUIRE(arr.Size() == 2);
	REQUIRE(arr.Capacity() == 2);
	REQUIRE(arr[0] == "hello");
	REQUIRE(arr[1] == "world");

	arr.Add("!");
	REQUIRE(arr.Size() == 3);
	REQUIRE(arr.Capacity() == 4);
	REQUIRE(arr[0] == "hello");
	REQUIRE(arr[1] == "world");
	REQUIRE(arr[2] == "!");
}

TEST_CASE("TestClearEmptyCMyArray")
{
	CMyArray<int> intArr;
	CMyArray<double> doubleArr;
	CMyArray<std::string> stringArr;

	intArr.Clear();
	doubleArr.Clear();
	stringArr.Clear();

	REQUIRE(intArr.Size() == 0);
	REQUIRE(intArr.Capacity() == 0);

	REQUIRE(doubleArr.Size() == 0);
	REQUIRE(doubleArr.Capacity() == 0);

	REQUIRE(stringArr.Size() == 0);
	REQUIRE(stringArr.Capacity() == 0);
}

TEST_CASE("TestClearIntCMyArray")
{
	CMyArray<int> arr;
	arr.Add(1);
	arr.Add(3);
	arr.Add(7);

	REQUIRE(arr.Size() == 3);
	REQUIRE(arr.Capacity() == 4);

	arr.Clear();
	REQUIRE(arr.Size() == 0);
	REQUIRE(arr.Capacity() == 0);
}

TEST_CASE("TestClearDoubleCMyArray")
{
	CMyArray<double> arr;
	arr.Add(1.5);
	arr.Add(3.89);
	arr.Add(-0.008);

	REQUIRE(arr.Size() == 3);
	REQUIRE(arr.Capacity() == 4);

	arr.Clear();
	REQUIRE(arr.Size() == 0);
	REQUIRE(arr.Capacity() == 0);
}

TEST_CASE("TestClearStringCMyArray")
{
	CMyArray<std::string> arr;
	arr.Add("hello");
	arr.Add("world");
	arr.Add("!");

	REQUIRE(arr.Size() == 3);
	REQUIRE(arr.Capacity() == 4);

	arr.Clear();
	REQUIRE(arr.Size() == 0);
	REQUIRE(arr.Capacity() == 0);
}

TEST_CASE("TestResizeEmptyIntCMyArray")
{
	CMyArray<int> arr;

	arr.Resize(0);
	REQUIRE(arr.Size() == 0);
	REQUIRE(arr.Capacity() == 0);

	arr.Resize(2);
	REQUIRE(arr.Size() == 2);
	REQUIRE(arr.Capacity() == 2);
	REQUIRE(arr[0] == 0);
	REQUIRE(arr[1] == 0);
}

TEST_CASE("TestResizeEmptyDoubleCMyArray")
{
	CMyArray<double> arr;

	arr.Resize(0);
	REQUIRE(arr.Size() == 0);
	REQUIRE(arr.Capacity() == 0);

	arr.Resize(2);
	REQUIRE(arr.Size() == 2);
	REQUIRE(arr.Capacity() == 2);
	REQUIRE(arr[0] == 0);
	REQUIRE(arr[1] == 0);
}

TEST_CASE("TestResizeEmptyStringCMyArray")
{
	CMyArray<std::string> arr;

	arr.Resize(0);
	REQUIRE(arr.Size() == 0);
	REQUIRE(arr.Capacity() == 0);

	arr.Resize(2);
	REQUIRE(arr.Size() == 2);
	REQUIRE(arr.Capacity() == 2);
	REQUIRE(arr[0] == "");
	REQUIRE(arr[1] == "");
}

TEST_CASE("TestResizeIntCMyArray")
{
	CMyArray<int> arr;
	arr.Add(1);
	arr.Add(3);
	arr.Add(7);
	REQUIRE(arr.Size() == 3);
	REQUIRE(arr.Capacity() == 4);
	REQUIRE(arr[0] == 1);
	REQUIRE(arr[1] == 3);
	REQUIRE(arr[2] == 7);

	arr.Resize(2);
	REQUIRE(arr.Size() == 2);
	REQUIRE(arr.Capacity() == 4);
	REQUIRE(arr[0] == 1);
	REQUIRE(arr[1] == 3);

	arr.Resize(4);
	REQUIRE(arr.Size() == 4);
	REQUIRE(arr.Capacity() == 4);
	REQUIRE(arr[0] == 1);
	REQUIRE(arr[1] == 3);
	REQUIRE(arr[2] == 0);
	REQUIRE(arr[3] == 0);
}

TEST_CASE("TestResizeDoubleCMyArray")
{
	CMyArray<double> arr;
	arr.Add(1.5);
	arr.Add(3.89);
	arr.Add(-0.008);
	REQUIRE(arr.Size() == 3);
	REQUIRE(arr.Capacity() == 4);
	REQUIRE(arr[0] == 1.5);
	REQUIRE(arr[1] == 3.89);
	REQUIRE(arr[2] == -0.008);

	arr.Resize(2);
	REQUIRE(arr.Size() == 2);
	REQUIRE(arr.Capacity() == 4);
	REQUIRE(arr[0] == 1.5);
	REQUIRE(arr[1] == 3.89);

	arr.Resize(4);
	REQUIRE(arr.Size() == 4);
	REQUIRE(arr.Capacity() == 4);
	REQUIRE(arr[0] == 1.5);
	REQUIRE(arr[1] == 3.89);
	REQUIRE(arr[2] == 0);
	REQUIRE(arr[3] == 0);
}

TEST_CASE("TestResizeStringCMyArray")
{
	CMyArray<std::string> arr;
	arr.Add("hello");
	arr.Add("world");
	arr.Add("!");
	REQUIRE(arr.Size() == 3);
	REQUIRE(arr.Capacity() == 4);
	REQUIRE(arr[0] == "hello");
	REQUIRE(arr[1] == "world");
	REQUIRE(arr[2] == "!");

	arr.Resize(2);
	REQUIRE(arr.Size() == 2);
	REQUIRE(arr.Capacity() == 4);
	REQUIRE(arr[0] == "hello");
	REQUIRE(arr[1] == "world");

	arr.Resize(4);
	REQUIRE(arr.Size() == 4);
	REQUIRE(arr.Capacity() == 4);
	REQUIRE(arr[0] == "hello");
	REQUIRE(arr[1] == "world");
	REQUIRE(arr[2] == "");
	REQUIRE(arr[3] == "");
}

TEST_CASE("TestIdexesAccessCMyArraySuccess")
{
	CMyArray<int> arr;
	arr.Add(1);
	arr.Add(3);
	arr.Add(7);

	REQUIRE(arr[0] == 1);
	REQUIRE(arr[1] == 3);
	REQUIRE(arr[2] == 7);

	arr[0] = 99;
	arr[2] = 999;

	REQUIRE(arr[0] == 99);
	REQUIRE(arr[1] == 3);
	REQUIRE(arr[2] == 999);
}

TEST_CASE("TestIdexesAccessCMyArrayFailed")
{
	CMyArray<int> arr;

	REQUIRE_THROWS_AS(arr[0], IndexOutOfRangeException);
	REQUIRE_THROWS_AS(arr[2], IndexOutOfRangeException);

	arr.Add(1);
	arr.Add(3);
	arr.Add(7);

	REQUIRE_THROWS_AS(arr[3], IndexOutOfRangeException);
}

TEST_CASE("TestRangeForIntCMyArray")
{
	CMyArray<int> intArr;
	intArr.Add(1);
	intArr.Add(3);
	intArr.Add(5);
	intArr.Add(7);

	std::vector<int> intVector;
	for (const auto& num : intArr)
	{
		intVector.push_back(num);
	}
	REQUIRE(intVector == std::vector<int>({ 1, 3, 5, 7 }));

	intVector.clear();
	for (auto it = intArr.begin(); it != intArr.end(); ++it)
	{
		intVector.push_back(*it);
	}
	REQUIRE(intVector == std::vector<int>({ 1, 3, 5, 7 }));
}

TEST_CASE("TestRangeForDoubleCMyArray")
{
	CMyArray<double> doubleArr;
	doubleArr.Add(1.5);
	doubleArr.Add(3.89);
	doubleArr.Add(5.67777);
	doubleArr.Add(0.0000009);

	std::vector<double> doubleVector;
	for (const auto& value : doubleArr)
	{
		doubleVector.push_back(value);
	}
	REQUIRE(doubleVector == std::vector<double>({ 1.5, 3.89, 5.67777, 0.0000009 }));

	doubleVector.clear();
	for (auto it = doubleArr.begin(); it != doubleArr.end(); ++it)
	{
		doubleVector.push_back(*it);
	}
	REQUIRE(doubleVector == std::vector<double>({ 1.5, 3.89, 5.67777, 0.0000009 }));
}

TEST_CASE("TestRangeForStringCMyArray")
{
	CMyArray<std::string> stringArr;
	stringArr.Add("hello");
	stringArr.Add("world");
	stringArr.Add("!");
	stringArr.Add("goodbie");

	std::vector<std::string> stringVector;
	for (const auto& string : stringArr)
	{
		stringVector.push_back(string);
	}
	REQUIRE(stringVector == std::vector<std::string>({ "hello", "world", "!", "goodbie" }));

	stringVector.clear();
	for (auto it = stringArr.begin(); it != stringArr.end(); ++it)
	{
		stringVector.push_back(*it);
	}
	REQUIRE(stringVector == std::vector<std::string>({ "hello", "world", "!", "goodbie" }));
}

TEST_CASE("TestReverseForIntCMyArray")
{
	CMyArray<int> intArr;
	intArr.Add(1);
	intArr.Add(3);
	intArr.Add(5);
	intArr.Add(7);

	std::vector<int> reversedVector;
	for (auto it = intArr.rbegin(); it != intArr.rend(); ++it)
	{
		reversedVector.push_back(*it);
	}
	REQUIRE(reversedVector == std::vector<int>({ 7, 5, 3, 1 }));
}

TEST_CASE("TestReverseForDoubleCMyArray")
{
	CMyArray<double> doubleArr;
	doubleArr.Add(1.5);
	doubleArr.Add(3.89);
	doubleArr.Add(5.67777);
	doubleArr.Add(0.0000009);

	std::vector<double> reversedVector;
	for (auto it = doubleArr.rbegin(); it != doubleArr.rend(); ++it)
	{
		reversedVector.push_back(*it);
	}
	REQUIRE(reversedVector == std::vector<double>({ 0.0000009, 5.67777, 3.89, 1.5 }));
}

TEST_CASE("TestReverseForStringCMyArray")
{
	CMyArray<std::string> stringArr;
	stringArr.Add("hello");
	stringArr.Add("world");
	stringArr.Add("!");
	stringArr.Add("goodbie");

	std::vector<std::string> reversedVector;
	for (auto it = stringArr.rbegin(); it != stringArr.rend(); ++it)
	{
		reversedVector.push_back(*it);
	}
	REQUIRE(reversedVector == std::vector<std::string>({ "goodbie", "!", "world", "hello" }));
}