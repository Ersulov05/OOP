#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

double GetSummPositiveElements(const std::vector<double>& numbers);

int GetCountPositiveElements(const std::vector<double>& numbers);

std::vector<double> ProcessNumbers(const std::vector<double>& numbers);

#endif