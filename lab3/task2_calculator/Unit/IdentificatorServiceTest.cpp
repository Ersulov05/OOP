#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Calculator/Exception/IdentificatorNameExistsException.h"
#include "../Calculator/Exception/IdentificatorNotFoundException.h"
#include "../Calculator/Exception/IdentificatorTypeNotIsVariableException.h"
#include "../Calculator/Repository/IdentificatorRepository.h"
#include "../Calculator/Service/IdentificatorService.h"
#include "../Calculator/Service/Input/FunctionIdentificatorInput.h"

TEST_CASE("TestCreateVariableIdentificatorSuccess")
{
	IdentificatorService identificatorService;

	std::string identificatorName = "x";
	identificatorService.CreateVariableIdentificator(identificatorName);

	IdentificatorValueData identificatorValueData = identificatorService.GetIdentificatorValueData(identificatorName);
	REQUIRE(identificatorValueData.identificatorName == identificatorName);
	REQUIRE(std::isnan(identificatorValueData.value));
}

TEST_CASE("TestCreateVariableIdentificatorNameExistsFailed")
{
	IdentificatorService identificatorService;

	std::string identificatorName = "x";
	identificatorService.CreateVariableIdentificator(identificatorName);
	REQUIRE_THROWS_AS(identificatorService.CreateVariableIdentificator(identificatorName), IdentificatorNameExistsException);
}

TEST_CASE("TestCreateFunctionIdentificatorSuccess")
{
	IdentificatorService identificatorService;

	std::string firstVariableIdentificatorName = "x";
	std::string secondVariableIdentificatorName = "y";
	identificatorService.CreateVariableIdentificator(firstVariableIdentificatorName);
	identificatorService.CreateVariableIdentificator(secondVariableIdentificatorName);

	std::string functionIdentificatorName = "fn1";
	std::string operation = "+";
	FunctionIdentificatorInput functionIdentificatorInput(
		functionIdentificatorName,
		firstVariableIdentificatorName,
		operation,
		secondVariableIdentificatorName);

	identificatorService.CreateFunctionIdentificator(functionIdentificatorInput);
	IdentificatorValueData identificatorValueData = identificatorService.GetIdentificatorValueData(functionIdentificatorName);

	REQUIRE(identificatorValueData.identificatorName == functionIdentificatorName);
	REQUIRE(std::isnan(identificatorValueData.value));

	std::string secondFunctionIdentificatorName = "fn2";
	FunctionIdentificatorInput secondFunctionIdentificatorInput(
		secondFunctionIdentificatorName,
		functionIdentificatorName,
		operation,
		functionIdentificatorName);

	identificatorService.CreateFunctionIdentificator(secondFunctionIdentificatorInput);
	identificatorValueData = identificatorService.GetIdentificatorValueData(secondFunctionIdentificatorName);

	REQUIRE(identificatorValueData.identificatorName == secondFunctionIdentificatorName);
	REQUIRE(std::isnan(identificatorValueData.value));
}

TEST_CASE("TestCreateFunctionIdentificatorNameExistsFailed")
{
	IdentificatorService identificatorService;

	std::string variableIdentificatorName = "x";
	identificatorService.CreateVariableIdentificator(variableIdentificatorName);

	std::string identificatorName = "x";
	FunctionIdentificatorInput functionIdentificatorInput(
		identificatorName,
		variableIdentificatorName);

	REQUIRE_THROWS_AS(identificatorService.CreateFunctionIdentificator(functionIdentificatorInput), IdentificatorNameExistsException);
}

TEST_CASE("TestCreateFunctionIdentificatorNotFoundFailed")
{
	IdentificatorService identificatorService;

	std::string variableIdentificatorName = "x";
	std::string identificatorName = "fn1";

	FunctionIdentificatorInput functionIdentificatorInput(
		identificatorName,
		variableIdentificatorName);

	REQUIRE_THROWS_AS(identificatorService.CreateFunctionIdentificator(functionIdentificatorInput), IdentificatorNotFoundException);
}

TEST_CASE("TestStoreVariableIdentificatorByValueSuccess")
{
	IdentificatorService identificatorService;

	std::string identificatorName = "x";
	double value = 10;
	identificatorService.StoreVariableIdentificatorByValue(identificatorName, value);

	IdentificatorValueData identificatorValueData = identificatorService.GetIdentificatorValueData(identificatorName);

	REQUIRE(identificatorValueData.identificatorName == identificatorName);
	REQUIRE(identificatorValueData.value == value);

	value = -100;
	identificatorService.StoreVariableIdentificatorByValue(identificatorName, value);
	identificatorValueData = identificatorService.GetIdentificatorValueData(identificatorName);

	REQUIRE(identificatorValueData.identificatorName == identificatorName);
	REQUIRE(identificatorValueData.value == value);
}

TEST_CASE("TestStoreVariableIdentificatorByValueTypeNotIsVariableFailed")
{
	IdentificatorService identificatorService;

	identificatorService.CreateVariableIdentificator("x");
	std::string functionName = "fn";
	FunctionIdentificatorInput functionIdentificatorInput(
		functionName,
		"x");
	identificatorService.CreateFunctionIdentificator(functionIdentificatorInput);

	double value = 10;
	REQUIRE_THROWS_AS(identificatorService.StoreVariableIdentificatorByValue(functionName, value), IdentificatorTypeNotIsVariableException);
}

TEST_CASE("TestStoreVariableIdentificatorByIdentificatorTypeNotIsVariableFailed")
{
	IdentificatorService identificatorService;

	std::string variableName = "x";
	identificatorService.CreateVariableIdentificator(variableName);
	std::string functionName = "fn";
	FunctionIdentificatorInput functionIdentificatorInput(
		functionName,
		variableName);
	identificatorService.CreateFunctionIdentificator(functionIdentificatorInput);

	REQUIRE_THROWS_AS(identificatorService.StoreVariableIdentificatorByIdentificator(functionName, variableName), IdentificatorTypeNotIsVariableException);

	std::string identificatorName = "y";
	identificatorService.StoreVariableIdentificatorByIdentificator(identificatorName, functionName);
	IdentificatorValueData valueData = identificatorService.GetIdentificatorValueData(identificatorName);
	REQUIRE(valueData.identificatorName == identificatorName);
}

TEST_CASE("TestStoreVariableIdentificatorByIdentificatorSuccess")
{
	IdentificatorService identificatorService;

	std::string firstIdentificatorName = "x";
	std::string secondIdentificatorName = "y";
	double firstIdentificatorValue = 10;
	double secondIdentificatorValue = 20;

	identificatorService.StoreVariableIdentificatorByValue(firstIdentificatorName, firstIdentificatorValue);
	identificatorService.StoreVariableIdentificatorByValue(secondIdentificatorName, secondIdentificatorValue);

	std::string thirdIdentificatorName = "z";
	identificatorService.StoreVariableIdentificatorByIdentificator(thirdIdentificatorName, firstIdentificatorName);

	auto firstValueData = identificatorService.GetIdentificatorValueData(firstIdentificatorName);
	auto secondValueData = identificatorService.GetIdentificatorValueData(secondIdentificatorName);
	auto thirdValueData = identificatorService.GetIdentificatorValueData(thirdIdentificatorName);

	REQUIRE(firstValueData.identificatorName == firstIdentificatorName);
	REQUIRE(firstValueData.value == firstIdentificatorValue);

	REQUIRE(secondValueData.identificatorName == secondIdentificatorName);
	REQUIRE(secondValueData.value == secondIdentificatorValue);

	REQUIRE(thirdValueData.identificatorName == thirdIdentificatorName);
	REQUIRE(thirdValueData.value == firstIdentificatorValue);
}

TEST_CASE("TestStoreVariableIdentificatorByIdentificatorNotFoundFailed")
{
	IdentificatorService identificatorService;

	std::string identificatorName = "x";
	REQUIRE_THROWS_AS(identificatorService.StoreVariableIdentificatorByIdentificator(identificatorName, "notFoundIdentificator"), IdentificatorNotFoundException);
}

TEST_CASE("TestFibonachi")
{
	IdentificatorService identificatorService;
	identificatorService.StoreVariableIdentificatorByValue("v0", 0);
	identificatorService.StoreVariableIdentificatorByValue("v1", 1);
	identificatorService.CreateFunctionIdentificator(FunctionIdentificatorInput("fib0", "v0"));
	identificatorService.CreateFunctionIdentificator(FunctionIdentificatorInput("fib1", "v1"));

	for (size_t i = 2; i < 51; i++)
	{
		identificatorService.CreateFunctionIdentificator(FunctionIdentificatorInput(
			"fib" + std::to_string(i),
			"fib" + std::to_string(i - 1),
			"+",
			"fib" + std::to_string(i - 2)));
	}

	auto functionValueData = identificatorService.GetIdentificatorValueData("fib50");
	REQUIRE(functionValueData.identificatorName == "fib50");
	REQUIRE(functionValueData.value == 12586269025);

	identificatorService.StoreVariableIdentificatorByValue("v0", 1);

	functionValueData = identificatorService.GetIdentificatorValueData("fib50");
	REQUIRE(functionValueData.identificatorName == "fib50");
	REQUIRE(functionValueData.value == 20365011074);
}

TEST_CASE("TestStack")
{
	IdentificatorService identificatorService;
	identificatorService.StoreVariableIdentificatorByValue("x", 1);
	identificatorService.CreateFunctionIdentificator(FunctionIdentificatorInput("x2", "x", "+", "x"));
	for (size_t i = 3; i <= 1000000; i++)
	{
		identificatorService.CreateFunctionIdentificator(FunctionIdentificatorInput(
			"x" + std::to_string(i),
			"x" + std::to_string(i - 1),
			"+",
			"x"));
	}

	auto functionValueData = identificatorService.GetIdentificatorValueData("x1000000");
	REQUIRE(functionValueData.identificatorName == "x1000000");
	REQUIRE(functionValueData.value == 1000000);

	identificatorService.StoreVariableIdentificatorByValue("x", 2);

	functionValueData = identificatorService.GetIdentificatorValueData("x1000000");
	REQUIRE(functionValueData.identificatorName == "x1000000");
	REQUIRE(functionValueData.value == 2000000);
}