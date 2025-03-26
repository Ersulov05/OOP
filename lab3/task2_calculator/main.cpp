#include "./AppCommand.h"
#include "./Calculator/Repository/IdentificatorRepository.h"
#include "./Calculator/Service/IdentificatorQueryService.h"
#include "./Calculator/Service/IdentificatorService.h"
#include <iostream>

int main(int argc, char* argv[])
{
	IdentificatorRepository identificatorRepository;
	IdentificatorService identificatorService(identificatorRepository);
	IdentificatorQueryService identificatorQueryService(identificatorRepository);

	identificatorService.CreateVariableIdentificator("var");
	identificatorService.EditVariableIdentificatorByValue("var", 5);

	identificatorService.CreateVariableIdentificator("varit");
	identificatorService.EditVariableIdentificatorByValue("varit", 7);

	identificatorService.CreateVariableIdentificator("varer");
	identificatorService.EditVariableIdentificatorByIdentificator("varer", "var");

	identificatorService.CreateFunctionIdentificator(FunctionIdentificatorInput("fn0", Operation::PLUS, "var", "varer"));

	for (int i = 1; i < 10000; ++i)
	{
		identificatorService.CreateFunctionIdentificator(FunctionIdentificatorInput("fn" + std::to_string(i), Operation::PLUS, "fn" + std::to_string(i - 1), "varer"));
	}

	auto identificatorValues = identificatorQueryService.GetVariableIdentificatorValuesData();
	for (const auto& identificatorValue : identificatorValues)
	{
		std::cout << identificatorValue.identificatorName << ": " << identificatorValue.value << std::endl;
	}

	auto functionIdentificatorValues = identificatorQueryService.GetFunctionIdentificatorValuesData();
	for (const auto& identificatorValue : functionIdentificatorValues)
	{
		std::cout << identificatorValue.identificatorName << ": " << identificatorValue.value << std::endl;
	}

	return 0;
}