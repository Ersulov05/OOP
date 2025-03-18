#pragma once
#include <string>
enum class Direction
{
	FORWARD,
	BACKWARD,
	STANDING_STILL,
};

std::string ConvertDirectionToString(const Direction direction);