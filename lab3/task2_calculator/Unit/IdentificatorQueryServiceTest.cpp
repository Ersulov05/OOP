#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Calculator/Exception/IdentificatorNameExistsException.h"
#include "../Calculator/Exception/IdentificatorNotFoundException.h"
#include "../Calculator/Exception/IdentificatorTypeNotIsVariableException.h"
#include "../Calculator/Repository/IdentificatorRepository.h"
#include "../Calculator/Service/IdentificatorQueryService.h"
#include "../Calculator/Service/IdentificatorService.h"
#include "../Calculator/Service/Input/FunctionIdentificatorInput.h"

TEST_CASE("TestGetIdentificatorValueDataSuccess")
{
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);
	IdentificatorQueryService identificatorQueryService(identificatorRepository);
	std::string firstVariableIdentificatorName = "x";
	std::string secondVariableIdentificatorName = "y";
	double secondVariableValue = 10;
	identificatorService.CreateVariableIdentificator(firstVariableIdentificatorName);
	identificatorService.StoreVariableIdentificatorByValue(secondVariableIdentificatorName, secondVariableValue);

	IdentificatorValueData identificatorValueData = identificatorQueryService.GetIdentificatorValueData(firstVariableIdentificatorName);
	REQUIRE(identificatorValueData.identificatorName == firstVariableIdentificatorName);
	REQUIRE(std::isnan(identificatorValueData.value));

	identificatorValueData = identificatorQueryService.GetIdentificatorValueData(secondVariableIdentificatorName);
	REQUIRE(identificatorValueData.identificatorName == secondVariableIdentificatorName);
	REQUIRE(identificatorValueData.value == secondVariableValue);

	std::string firstFunctionIdentificatorName = "z";
	std::string secondFunctionIdentificatorName = "a";
	std::string thirdFunctionIdentificatorName = "b";
	identificatorRepository.AddIdentificator(Identificator(firstFunctionIdentificatorName, Function(Operation::NONE, secondVariableIdentificatorName)));
	identificatorRepository.AddIdentificator(Identificator(secondFunctionIdentificatorName, Function(Operation::PLUS, secondVariableIdentificatorName, firstFunctionIdentificatorName)));
	identificatorRepository.AddIdentificator(Identificator(thirdFunctionIdentificatorName, Function(Operation::PLUS, secondFunctionIdentificatorName, firstVariableIdentificatorName)));

	identificatorValueData = identificatorQueryService.GetIdentificatorValueData(firstFunctionIdentificatorName);
	REQUIRE(identificatorValueData.identificatorName == firstFunctionIdentificatorName);
	REQUIRE(identificatorValueData.value == secondVariableValue);

	identificatorValueData = identificatorQueryService.GetIdentificatorValueData(secondFunctionIdentificatorName);
	REQUIRE(identificatorValueData.identificatorName == secondFunctionIdentificatorName);
	REQUIRE(identificatorValueData.value == secondVariableValue + secondVariableValue);

	identificatorValueData = identificatorQueryService.GetIdentificatorValueData(thirdFunctionIdentificatorName);
	REQUIRE(identificatorValueData.identificatorName == thirdFunctionIdentificatorName);
	REQUIRE(std::isnan(identificatorValueData.value));
}

TEST_CASE("TestGetIdentificatorValueDataAfterUpdatedVariableIdentificatorValueSuccess")
{
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);
	IdentificatorQueryService identificatorQueryService(identificatorRepository);
	std::string firstVariableIdentificatorName = "x";
	std::string secondVariableIdentificatorName = "y";
	double secondVariableValue = 10;
	identificatorService.CreateVariableIdentificator(firstVariableIdentificatorName);
	identificatorService.StoreVariableIdentificatorByValue(secondVariableIdentificatorName, secondVariableValue);

	std::string firstFunctionIdentificatorName = "a";
	std::string secondFunctionIdentificatorName = "b";
	std::string thirdFunctionIdentificatorName = "c";
	identificatorRepository.AddIdentificator(Identificator(firstFunctionIdentificatorName, Function(Operation::NONE, secondVariableIdentificatorName)));
	identificatorRepository.AddIdentificator(Identificator(secondFunctionIdentificatorName, Function(Operation::PLUS, secondVariableIdentificatorName, firstFunctionIdentificatorName)));
	identificatorRepository.AddIdentificator(Identificator(thirdFunctionIdentificatorName, Function(Operation::PLUS, secondFunctionIdentificatorName, firstVariableIdentificatorName)));

	IdentificatorValueData identificatorValueData = identificatorQueryService.GetIdentificatorValueData(firstFunctionIdentificatorName);
	REQUIRE(identificatorValueData.identificatorName == firstFunctionIdentificatorName);
	REQUIRE(identificatorValueData.value == secondVariableValue);

	identificatorValueData = identificatorQueryService.GetIdentificatorValueData(secondFunctionIdentificatorName);
	REQUIRE(identificatorValueData.identificatorName == secondFunctionIdentificatorName);
	REQUIRE(identificatorValueData.value == secondVariableValue + secondVariableValue);

	identificatorValueData = identificatorQueryService.GetIdentificatorValueData(thirdFunctionIdentificatorName);
	REQUIRE(identificatorValueData.identificatorName == thirdFunctionIdentificatorName);
	REQUIRE(std::isnan(identificatorValueData.value));

	double editedFirstVariableValue = 10;
	double editedSecondVariableValue = 20;
	identificatorService.StoreVariableIdentificatorByValue(firstVariableIdentificatorName, editedFirstVariableValue);
	identificatorService.StoreVariableIdentificatorByValue(secondVariableIdentificatorName, editedSecondVariableValue);
	identificatorQueryService.ClearCache();

	identificatorValueData = identificatorQueryService.GetIdentificatorValueData(secondVariableIdentificatorName);
	REQUIRE(identificatorValueData.identificatorName == secondVariableIdentificatorName);
	REQUIRE(identificatorValueData.value == editedSecondVariableValue);

	identificatorValueData = identificatorQueryService.GetIdentificatorValueData(firstFunctionIdentificatorName);
	REQUIRE(identificatorValueData.identificatorName == firstFunctionIdentificatorName);
	REQUIRE(identificatorValueData.value == editedSecondVariableValue);

	identificatorValueData = identificatorQueryService.GetIdentificatorValueData(secondFunctionIdentificatorName);
	REQUIRE(identificatorValueData.identificatorName == secondFunctionIdentificatorName);
	REQUIRE(identificatorValueData.value == editedSecondVariableValue + editedSecondVariableValue);

	identificatorValueData = identificatorQueryService.GetIdentificatorValueData(thirdFunctionIdentificatorName);
	REQUIRE(identificatorValueData.identificatorName == thirdFunctionIdentificatorName);
	REQUIRE(identificatorValueData.value == editedSecondVariableValue + editedSecondVariableValue + editedFirstVariableValue);
}

TEST_CASE("TestGetIdentificatorValueDataNotFoundFailed")
{
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);
	IdentificatorQueryService identificatorQueryService(identificatorRepository);

	REQUIRE_THROWS_AS(identificatorQueryService.GetIdentificatorValueData("notFoundIdentificatorName"), IdentificatorNotFoundException);
}

TEST_CASE("TestGetVariableIdentificatorValuesDataSuccess")
{
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);
	IdentificatorQueryService identificatorQueryService(identificatorRepository);

	std::vector<IdentificatorValueData> identificatorValues = identificatorQueryService.GetVariableIdentificatorValuesData();
	REQUIRE(identificatorValues.size() == 0);

	identificatorService.CreateVariableIdentificator("x");
	identificatorValues = identificatorQueryService.GetVariableIdentificatorValuesData();
	REQUIRE(identificatorValues.size() == 1);

	identificatorService.CreateVariableIdentificator("y");
	identificatorValues = identificatorQueryService.GetVariableIdentificatorValuesData();
	REQUIRE(identificatorValues.size() == 2);

	identificatorRepository.AddIdentificator(Identificator("z", Function(Operation::NONE, "x")));
	identificatorValues = identificatorQueryService.GetVariableIdentificatorValuesData();
	REQUIRE(identificatorValues.size() == 2);
}

TEST_CASE("TestGetFunctionIdentificatorValuesDataSuccess")
{
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);
	IdentificatorQueryService identificatorQueryService(identificatorRepository);

	identificatorService.CreateVariableIdentificator("x");
	identificatorService.CreateVariableIdentificator("y");

	std::vector<IdentificatorValueData> identificatorValues = identificatorQueryService.GetFunctionIdentificatorValuesData();
	REQUIRE(identificatorValues.size() == 0);

	identificatorRepository.AddIdentificator(Identificator("z", Function(Operation::NONE, "x")));
	identificatorValues = identificatorQueryService.GetFunctionIdentificatorValuesData();
	REQUIRE(identificatorValues.size() == 1);

	identificatorRepository.AddIdentificator(Identificator("a", Function(Operation::PLUS, "x", "z")));
	identificatorValues = identificatorQueryService.GetFunctionIdentificatorValuesData();
	REQUIRE(identificatorValues.size() == 2);

	identificatorRepository.AddIdentificator(Identificator("b", Function(Operation::MINUS, "z", "a")));
	identificatorValues = identificatorQueryService.GetFunctionIdentificatorValuesData();
	REQUIRE(identificatorValues.size() == 3);
}