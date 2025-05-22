#include "./FindMaxEx.h"

template <typename T, typename Less>
bool FindMaxEx(const std::vector<T>& arr, T& maxValue, const Less& less)
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