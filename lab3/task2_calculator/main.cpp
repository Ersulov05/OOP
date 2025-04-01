#include "./AppCommand.h"
#include "./Controller/CalculateCommand.h"
#include "./Controller/CalculateController.h"
#include <iostream>

const std::string EXIT_STRING = "exit";

void Process(std::istream& input, std::ostream& output)
{
	CalculateController calculateController;
	while (true)
	{
		AppCommand appCommand = GetAppCommand(input);
		if (appCommand.stringCommand == EXIT_STRING)
		{
			return;
		}
		CalculateCommand calculateCommand = CreateCalculateCommand(appCommand);
		calculateController.HandleCalculateCommand(output, calculateCommand);
	}
}

int main(int argc, char* argv[])
{
	Process(std::cin, std::cout);
	return 0;
}