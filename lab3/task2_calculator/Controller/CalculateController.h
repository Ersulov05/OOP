#pragma once
#include "../Calculator/Service/IdentificatorQueryService.h"
#include "../Calculator/Service/IdentificatorService.h"
#include <string>
#include <vector>

enum class CalculateCommandType
{
	VAR,
	LET,
	FN,
	PRINT,
	PRINTVARS,
	PRINTFNS,
};

struct CalculateCommand
{
	CalculateCommandType type;
	std::vector<std::string> stringArgs;
};

class CalculateController
{
public:
	CalculateController(IdentificatorRepository& identificatorRepository);
	void HandleCalculateCommand(std::ostream& output, const CalculateCommand& calculateCommand);

private:
	void ExecuteCalculateCommand(std::ostream& output, const CalculateCommand& command);
	IdentificatorQueryService m_identificatorQueryService;
	IdentificatorService m_identificatorService;
};