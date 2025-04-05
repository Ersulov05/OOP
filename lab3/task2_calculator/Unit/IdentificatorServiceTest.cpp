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
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);

	std::string identificatorName = "x";
	identificatorService.CreateVariableIdentificator(identificatorName);

	std::optional<Identificator> identificator = identificatorRepository.GetIdentificatorByName(identificatorName);
	REQUIRE(identificator.has_value() == true);
	REQUIRE(identificator->name == identificatorName);
	REQUIRE(identificator->type == IdentificatorType::VARIABLE);
}

TEST_CASE("TestCreateVariableIdentificatorNameExistsFailed")
{
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);

	std::string identificatorName = "x";
	identificatorService.CreateVariableIdentificator(identificatorName);
	REQUIRE_THROWS_AS(identificatorService.CreateVariableIdentificator(identificatorName), IdentificatorNameExistsException);
}

TEST_CASE("TestCreateFunctionIdentificatorSuccess")
{
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);

	std::string firstVariableIdentificatorName = "x";
	std::string secondVariableIdentificatorName = "y";
	identificatorService.CreateVariableIdentificator(firstVariableIdentificatorName);
	identificatorService.CreateVariableIdentificator(secondVariableIdentificatorName);

	std::string functionIdentificatorName = "fn1";
	Operation operation = Operation::PLUS;
	FunctionIdentificatorInput functionIdentificatorInput(
		functionIdentificatorName,
		operation,
		firstVariableIdentificatorName,
		secondVariableIdentificatorName);

	identificatorService.CreateFunctionIdentificator(functionIdentificatorInput);
	std::optional<Identificator> identificator = identificatorRepository.GetIdentificatorByName(functionIdentificatorName);

	REQUIRE(identificator.has_value() == true);
	REQUIRE(identificator->name == functionIdentificatorName);
	REQUIRE(identificator->type == IdentificatorType::FUNCTION);
	Function* function = identificator->data.function;
	REQUIRE(function->firstIdentificatorName == firstVariableIdentificatorName);
	REQUIRE(function->secondIdentificatorName == secondVariableIdentificatorName);
	REQUIRE(function->operation == operation);

	std::string secondFunctionIdentificatorName = "fn2";
	FunctionIdentificatorInput secondFunctionIdentificatorInput(
		secondFunctionIdentificatorName,
		operation,
		functionIdentificatorName,
		functionIdentificatorName);

	identificatorService.CreateFunctionIdentificator(secondFunctionIdentificatorInput);
	identificator = identificatorRepository.GetIdentificatorByName(secondFunctionIdentificatorName);

	REQUIRE(identificator.has_value() == true);
	REQUIRE(identificator->name == secondFunctionIdentificatorName);
	REQUIRE(identificator->type == IdentificatorType::FUNCTION);
	function = identificator->data.function;
	REQUIRE(function->firstIdentificatorName == functionIdentificatorName);
	REQUIRE(function->secondIdentificatorName == functionIdentificatorName);
	REQUIRE(function->operation == operation);
}

TEST_CASE("TestCreateFunctionIdentificatorNameExistsFailed")
{
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);

	std::string variableIdentificatorName = "x";
	identificatorService.CreateVariableIdentificator(variableIdentificatorName);

	std::string identificatorName = "x";
	Operation operation = Operation::PLUS;
	FunctionIdentificatorInput functionIdentificatorInput(
		identificatorName,
		Operation::NONE,
		variableIdentificatorName);

	REQUIRE_THROWS_AS(identificatorService.CreateFunctionIdentificator(functionIdentificatorInput), IdentificatorNameExistsException);
}

TEST_CASE("TestCreateFunctionIdentificatorNotFoundFailed")
{
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);

	std::string variableIdentificatorName = "x";
	std::string identificatorName = "fn1";

	Operation operation = Operation::PLUS;
	FunctionIdentificatorInput functionIdentificatorInput(
		identificatorName,
		Operation::NONE,
		variableIdentificatorName);

	REQUIRE_THROWS_AS(identificatorService.CreateFunctionIdentificator(functionIdentificatorInput), IdentificatorNotFoundException);
}

TEST_CASE("TestStoreVariableIdentificatorByValueSuccess")
{
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);

	std::string identificatorName = "x";
	double value = 10;
	identificatorService.StoreVariableIdentificatorByValue(identificatorName, value);

	std::optional<Identificator> identificator = identificatorRepository.GetIdentificatorByName(identificatorName);
	REQUIRE(identificator.has_value() == true);
	REQUIRE(identificator->name == identificatorName);
	REQUIRE(identificator->type == IdentificatorType::VARIABLE);
	REQUIRE(identificator->data.value == value);

	value = -100;
	identificatorService.StoreVariableIdentificatorByValue(identificatorName, value);
	identificator = identificatorRepository.GetIdentificatorByName(identificatorName);
	REQUIRE(identificator.has_value() == true);
	REQUIRE(identificator->name == identificatorName);
	REQUIRE(identificator->type == IdentificatorType::VARIABLE);
	REQUIRE(identificator->data.value == value);
}

TEST_CASE("TestStoreVariableIdentificatorByValueTypeNotIsVariableFailed")
{
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);

	std::string identificatorName = "x";
	identificatorRepository.AddIdentificator(Identificator(identificatorName, Function(Operation::NONE, "y")));

	double value = 10;
	REQUIRE_THROWS_AS(identificatorService.StoreVariableIdentificatorByValue(identificatorName, value), IdentificatorTypeNotIsVariableException);
}

TEST_CASE("TestStoreVariableIdentificatorByIdentificatorSuccess")
{
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);

	std::string firstIdentificatorName = "x";
	std::string secondIdentificatorName = "y";
	double firstIdentificatorValue = 10;
	double secondIdentificatorValue = 20;

	identificatorService.StoreVariableIdentificatorByValue(firstIdentificatorName, firstIdentificatorValue);
	identificatorService.StoreVariableIdentificatorByValue(secondIdentificatorName, secondIdentificatorValue);

	std::string thirdIdentificatorName = "z";
	identificatorService.StoreVariableIdentificatorByIdentificator(thirdIdentificatorName, firstIdentificatorName);

	std::optional<Identificator> identificator = identificatorRepository.GetIdentificatorByName(thirdIdentificatorName);
	REQUIRE(identificator.has_value() == true);
	REQUIRE(identificator->name == thirdIdentificatorName);
	REQUIRE(identificator->type == IdentificatorType::VARIABLE);
	REQUIRE(identificator->data.value == firstIdentificatorValue);

	identificatorService.StoreVariableIdentificatorByIdentificator(thirdIdentificatorName, secondIdentificatorName);

	identificator = identificatorRepository.GetIdentificatorByName(thirdIdentificatorName);
	REQUIRE(identificator.has_value() == true);
	REQUIRE(identificator->name == thirdIdentificatorName);
	REQUIRE(identificator->type == IdentificatorType::VARIABLE);
	REQUIRE(identificator->data.value == secondIdentificatorValue);
}

TEST_CASE("TestStoreVariableIdentificatorByIdentificatorNotFoundFailed")
{
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);

	std::string identificatorName = "x";
	REQUIRE_THROWS_AS(identificatorService.StoreVariableIdentificatorByIdentificator(identificatorName, "notFoundIdentificator"), IdentificatorNotFoundException);
}

TEST_CASE("TestStoreVariableIdentificatorByIdentificatorTypeNotIsVariableFailed")
{
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);

	std::string functionIdentificatorName = "x";
	identificatorRepository.AddIdentificator(Identificator(functionIdentificatorName, Function(Operation::NONE, "y")));

	std::string identificatorName = "y";
	REQUIRE_THROWS_AS(identificatorService.StoreVariableIdentificatorByIdentificator(identificatorName, functionIdentificatorName), IdentificatorTypeNotIsVariableException);
	identificatorService.StoreVariableIdentificatorByValue(identificatorName, 10);

	REQUIRE_THROWS_AS(identificatorService.StoreVariableIdentificatorByIdentificator(functionIdentificatorName, identificatorName), IdentificatorTypeNotIsVariableException);
}