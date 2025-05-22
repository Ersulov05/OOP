#pragma once
#include <vector>

template <typename T, typename Less>
inline bool FindMaxEx(const std::vector<T>& arr, T& maxValue, const Less& less);