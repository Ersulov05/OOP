#pragma once
#include <iostream>

class GearsNotLinkedException : public std::logic_error
{
public:
	GearsNotLinkedException()
		: std::logic_error("Gears not linked"){};
};