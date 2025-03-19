#pragma once
#include "../Calculator/Service/IdentificatorQueryService.h"
#include "../Calculator/Service/IdentificatorService.h"

class CalculateController
{
public:
	CalculateController();

private:
	IdentificatorQueryService identificatorQueryService;
	IdentificatorService identificatorService;
};