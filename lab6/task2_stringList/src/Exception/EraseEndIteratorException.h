#pragma once
#include <iostream>

class EraseEndIteratorException : public std::logic_error
{
public:
	EraseEndIteratorException()
		: std::logic_error("Cannot erase the end iterator"){};
};