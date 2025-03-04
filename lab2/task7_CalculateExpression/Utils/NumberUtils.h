#pragma once
#include "../Exception/ValueOutOfRangeException.h"
#include "iostream"

const int RADIX = 10;

int GetDigit(char ch);

bool IsDigit(char ch);

int GetNegativeCoef(std::istream& input);

int AddDigitToValue(int value, char ch);