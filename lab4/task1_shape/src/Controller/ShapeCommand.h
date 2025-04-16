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
	RUN_WINDOW,
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

ShapeCommandType GetShapeCommandTypeByString(const std::string& string);
ShapeCommand CreateShapeCommand(const AppCommand& appCommand);
