#include "Exception/InvalidValueException.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <regex>
#include <vector>

double RoundToDecimal(double number, int decimals);

double StringToDouble(const std::string& string);

double GetSummPositiveElements(const std::vector<double>& numbers);

int GetCountPositiveElements(const std::vector<double>& numbers);

std::vector<double> ProcessNumbers(const std::vector<double>& numbers);