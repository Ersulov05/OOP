#pragma once
#include "../Calculator/Service/IdentificatorService.h"
#include "./CalculatorCommand.h"
#include <string>

class CalculatorController
{
public:
	CalculatorController();
	void HandleCalculatorCommand(std::ostream& output, const CalculatorCommand& calculateCommand);
	void Load();

private:
	void ExecuteCalculatorCommand(std::ostream& output, const CalculatorCommand& command);
	void PrintIdentificatorValuesData(std::ostream& output, const std::vector<IdentificatorValueData>& identificatorValuesData);
	void CreateFunction(const CalculatorCommand& command);
	void CreateVariableWithValue(const CalculatorCommand& command);
	void CreateVariable(const CalculatorCommand& command);
	std::string GetIdentificatorName(const CalculatorCommand& command);

	IdentificatorService m_identificatorService;
};