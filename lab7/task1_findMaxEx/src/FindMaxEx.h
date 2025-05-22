#pragma once
#include <vector>

template <typename T, typename Less>
inline bool FindMaxEx(const std::vector<T>& arr, T& maxValue, const Less& less)
{
	if (arr.empty())
	{
		return false;
	}

	auto max = arr[0];
	for (const auto& elem : arr)
	{
		if (less(max, elem))
		{
			max = elem;
		}
	}
	maxValue = max;

	return true;
}