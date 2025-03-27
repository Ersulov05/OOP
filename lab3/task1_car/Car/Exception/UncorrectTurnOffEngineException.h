#pragma once
#include <iostream>

class UncorrectTurnOffEngineException : public std::runtime_error
{
public:
	UncorrectTurnOffEngineException()
		: std::runtime_error("Сar must be stopped and in neutral gear"){};
};