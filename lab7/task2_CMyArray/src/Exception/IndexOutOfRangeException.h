#pragma once
#include <iostream>

class IndexOutOfRangeException : public std::out_of_range
{
public:
	IndexOutOfRangeException()
		: std::out_of_range("Index out of range"){};
};