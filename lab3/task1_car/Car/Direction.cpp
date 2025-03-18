#include "Direction.h"

std::string ConvertDirectionToString(const Direction direction)
{
	switch (direction)
	{
	case Direction::FORWARD:
		return "Forward";
	case Direction::BACKWARD:
		return "Backward";
	case Direction::STANDING_STILL:
		return "Standing still";
	default:
		return "Unknown";
	}
}