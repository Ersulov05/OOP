#include "./AppCommand.h"
#include "./Controller/CalculatorCommand.h"
#include "./Controller/CalculatorController.h"
#include <iostream>

const std::string EXIT_STRING = "exit";

void Process(std::istream& input, std::ostream& output)
{
	CalculatorController calculatorController;
	while (true)
	{
		AppCommand appCommand = GetAppCommand(input);
		if (appCommand.stringCommand == EXIT_STRING)
		{
			return;
		}
		CalculatorCommand calculatorCommand = CreateCalculatorCommand(appCommand);
		calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	}
}

int main(int argc, char* argv[])
{
	Process(std::cin, std::cout);
	return 0;
}