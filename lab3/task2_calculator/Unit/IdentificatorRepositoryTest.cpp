#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Calculator/Entity/FunctionIdentificator.h"
#include "../Calculator/Entity/VariableIdentificator.h"
#include "../Calculator/Repository/IdentificatorRepository.h"
#include "../Controller/Exception/InvalidCalculatorCommandArgumentsException.h"
#include <sstream>

TEST_CASE("TestIdentificatorRepositoryStoreVariableIdentificator")
{
	IdentificatorRepository identificatorRepository;

	std::string variableIdentificatorName = "x";
	double variableValue = 10;
	auto variableIdentificator = new VariableIdentificator(variableIdentificatorName, variableValue);
	identificatorRepository.StoreIdentificator(variableIdentificator);

	auto identificator = identificatorRepository.GetIdentificatorByName(variableIdentificatorName);
	REQUIRE(dynamic_cast<VariableIdentificator*>(identificator) != nullptr);
	REQUIRE(identificator->GetName() == variableIdentificatorName);
	REQUIRE(identificator->IsCacheValid() == true);
	REQUIRE(identificator->GetValue() == variableValue);

	identificatorRepository.StoreIdentificator(variableIdentificator);
}

TEST_CASE("TestIdentificatorRepositoryStoreFunctionIdentificator")
{
	IdentificatorRepository identificatorRepository;

	std::string variableIdentificatorName = "x";
	double variableValue = 10;
	auto variableIdentificator = new VariableIdentificator(variableIdentificatorName, variableValue);
	identificatorRepository.StoreIdentificator(variableIdentificator);

	std::string functionIdentificatorName = "f";
	auto functionIdentificator = new FunctionIdentificator(functionIdentificatorName, variableIdentificator);
	identificatorRepository.StoreIdentificator(functionIdentificator);

	auto identificator = identificatorRepository.GetIdentificatorByName(functionIdentificatorName);
	REQUIRE(dynamic_cast<FunctionIdentificator*>(identificator) != nullptr);
	REQUIRE(identificator->GetName() == functionIdentificatorName);
	REQUIRE(identificator->IsCacheValid() == false);
	REQUIRE(identificator->GetValue() == variableValue);
	REQUIRE(identificator->IsCacheValid() == true);
	REQUIRE(identificator->GetSubscribes().size() == 1);
}

TEST_CASE("TestIdentificatorRepositoryGetFunctions")
{
	IdentificatorRepository identificatorRepository;

	auto variableIdentificator = new VariableIdentificator("x", 10);
	identificatorRepository.StoreIdentificator(variableIdentificator);

	auto functionIdentificator = new FunctionIdentificator("f0", variableIdentificator);
	identificatorRepository.StoreIdentificator(functionIdentificator);

	functionIdentificator = new FunctionIdentificator("f1", variableIdentificator);
	identificatorRepository.StoreIdentificator(functionIdentificator);

	auto functions = identificatorRepository.GetFunctions();
	REQUIRE(functions.size() == 2);

	for (const auto& function : functions)
	{
		REQUIRE(dynamic_cast<FunctionIdentificator*>(function) != nullptr);
	}
}

TEST_CASE("TestIdentificatorRepositoryGetVariables")
{
	IdentificatorRepository identificatorRepository;

	auto variableIdentificator = new VariableIdentificator("x", 10);
	identificatorRepository.StoreIdentificator(variableIdentificator);
	variableIdentificator = new VariableIdentificator("y", 15);
	identificatorRepository.StoreIdentificator(variableIdentificator);
	variableIdentificator = new VariableIdentificator("z", 30);
	identificatorRepository.StoreIdentificator(variableIdentificator);

	auto functionIdentificator = new FunctionIdentificator("f0", variableIdentificator);
	identificatorRepository.StoreIdentificator(functionIdentificator);
	functionIdentificator = new FunctionIdentificator("f1", variableIdentificator);
	identificatorRepository.StoreIdentificator(functionIdentificator);

	auto variables = identificatorRepository.GetVariables();
	REQUIRE(variables.size() == 3);

	for (const auto& variable : variables)
	{
		REQUIRE(dynamic_cast<VariableIdentificator*>(variable) != nullptr);
	}
}