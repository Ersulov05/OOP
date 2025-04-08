#pragma once
#include "../../AppCommand.h"
#include <string>
#include <vector>

enum class ShapeCommandType
{
	RECTANGLE,
	TRIANGLE,
	CIRCLE,
	LINE,
	PRINT_ALL,
	SHAPE_WITH_MAX_AREA,
	SHAPE_WITH_MIN_PERIMETER,
	NONE
};

struct ShapeCommand
{
	ShapeCommandType type;
	std::vector<std::string> stringArgs;

	ShapeCommand(ShapeCommandType type, std::vector<std::string> stringArgs)
		: type(type)
		, stringArgs(stringArgs){};
};

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
	return ShapeCommandType::NONE;
}

ShapeCommand CreateShapeCommand(const AppCommand& appCommand)
{
	ShapeCommandType type = GetShapeCommandTypeByString(appCommand.stringCommand);
	return ShapeCommand(type, appCommand.stringArgs);
}
