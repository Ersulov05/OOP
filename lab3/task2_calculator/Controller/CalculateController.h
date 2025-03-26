#pragma once
#include "../Calculator/Service/IdentificatorQueryService.h"
#include "../Calculator/Service/IdentificatorService.h"
#include "./CalculateCommand.h"

class CalculateController
{
public:
	CalculateController(IdentificatorRepository& identificatorRepository);
	void HandleCalculateCommand(std::ostream& output, const CalculateCommand& calculateCommand);

private:
	void ExecuteCalculateCommand(std::ostream& output, const CalculateCommand& command);
	void CreateFunction(const CalculateCommand& command);
	void CreateVariableWithValue(const CalculateCommand& command);
	void CreateVariable(const CalculateCommand& command);
	IdentificatorQueryService m_identificatorQueryService;
	IdentificatorService m_identificatorService;
};