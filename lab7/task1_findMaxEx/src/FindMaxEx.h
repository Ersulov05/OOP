#pragma once
#include <algorithm>
#include <vector>

template <typename T, typename Less>
inline bool FindMaxEx(const std::vector<T>& arr, T& maxValue, const Less& less)
{
	if (arr.empty())
	{
		return false;
	}

	auto it = std::max_element(arr.begin(), arr.end(), less);
	maxValue = *it;

	return true;
}