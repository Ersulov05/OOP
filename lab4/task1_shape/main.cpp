#include "./AppCommand.h"
#include "./src/Canvas/CCanvas.h"
#include "./src/Controller/ShapeCommand.h"
#include "./src/Controller/ShapeController.h"
#include <iostream>

const std::string EXIT_STRING = "exit";
const std::string START_COMMAND_SYMBOL = ">";

void Process(std::istream& input, std::ostream& output)
{
	ShapeController shapeController;
	while (true)
	{
		output << START_COMMAND_SYMBOL;
		AppCommand appCommand = GetAppCommand(input);
		if (appCommand.stringCommand == EXIT_STRING || input.eof())
		{
			break;
		}
		ShapeCommand shapeCommand = CreateShapeCommand(appCommand);
		shapeController.HandleShapeCommand(shapeCommand, output);
	}
	shapeController.RunWindow();
	shapeController.PrintShapeWithMaxArea(output);
	shapeController.PrintShapeWithMinPerimeter(output);
}

int main()
{
	Process(std::cin, std::cout);
	return 0;
}