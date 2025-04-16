#include "./ShapeCommand.h"

ShapeCommandType GetShapeCommandTypeByString(const std::string& string)
{
	if (string == "rectangle")
		return ShapeCommandType::RECTANGLE;
	if (string == "triangle")
		return ShapeCommandType::TRIANGLE;
	if (string == "circle")
		return ShapeCommandType::CIRCLE;
	if (string == "line")
		return ShapeCommandType::LINE;
	if (string == "printAll")
		return ShapeCommandType::PRINT_ALL;
	if (string == "maxArea")
		return ShapeCommandType::SHAPE_WITH_MAX_AREA;
	if (string == "minPerimeter")
		return ShapeCommandType::SHAPE_WITH_MIN_PERIMETER;
	if (string == "runWindow")
		return ShapeCommandType::RUN_WINDOW;
	return ShapeCommandType::NONE;
}

ShapeCommand CreateShapeCommand(const AppCommand& appCommand)
{
	ShapeCommandType type = GetShapeCommandTypeByString(appCommand.stringCommand);
	return ShapeCommand(type, appCommand.stringArgs);
}
