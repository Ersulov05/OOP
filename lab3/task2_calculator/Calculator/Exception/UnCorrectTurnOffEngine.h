#pragma once
#include <iostream>

class UnCorrectTurnOffEngine : public std::runtime_error
{
public:
	UnCorrectTurnOffEngine()
		: std::runtime_error("Сar must be stopped and in neutral gear"){};
};