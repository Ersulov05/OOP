#pragma once
#include "../Calculator/Service/IdentificatorQueryService.h"
#include "../Calculator/Service/IdentificatorService.h"
#include "./CalculateCommand.h"

class CalculateController
{
public:
	CalculateController();
	void HandleCalculateCommand(std::ostream& output, const CalculateCommand& calculateCommand);

private:
	void ExecuteCalculateCommand(std::ostream& output, const CalculateCommand& command);
	void PrintIdentificatorValuesData(std::ostream& output, const std::vector<IdentificatorValueData>& identificatorValuesData);
	void CreateFunction(const CalculateCommand& command);
	void CreateVariableWithValue(const CalculateCommand& command);
	void CreateVariable(const CalculateCommand& command);
	IdentificatorQueryService m_identificatorQueryService;
	IdentificatorService m_identificatorService;
	IdentificatorRepository m_identificatorRepository;
};