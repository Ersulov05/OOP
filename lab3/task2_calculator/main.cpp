#include "./AppCommand.h"
#include "./Calculator/Repository/IdentificatorRepository.h"
#include "./Calculator/Service/IdentificatorQueryService.h"
#include "./Calculator/Service/IdentificatorService.h"
#include "./Controller/CalculateCommand.h"
#include "./Controller/CalculateController.h"
#include <iostream>

void Process(std::istream& input, std::ostream& output)
{
	IdentificatorRepository identificatorRepository;
	CalculateController calculateController(identificatorRepository);
	while (true)
	{
		AppCommand appCommand = GetAppCommand(input);
		CalculateCommand calculateCommand = CreateCalculateCommand(appCommand);
		calculateController.HandleCalculateCommand(output, calculateCommand);
	}
}

int main(int argc, char* argv[])
{
	Process(std::cin, std::cout);

	return 0;
}