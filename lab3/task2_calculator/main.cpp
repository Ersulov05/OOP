#include "./AppCommand.h"
#include "./Controller/CalculatorCommand.h"
#include "./Controller/CalculatorController.h"
#include <iostream>

const std::string EXIT_STRING = "exit";
const std::string START_COMMAND_SYMBOL = ">";

void HandleCalculator(std::istream& input, std::ostream& output)
{
	CalculatorController calculatorController;
	while (true)
	{
		output << START_COMMAND_SYMBOL;
		AppCommand appCommand = GetAppCommand(input);
		if (appCommand.stringCommand == EXIT_STRING)
		{
			return;
		}
		CalculatorCommand calculatorCommand = CreateCalculatorCommand(appCommand);
		calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	}
}

int main()
{
	HandleCalculator(std::cin, std::cout);

	return 0;
}