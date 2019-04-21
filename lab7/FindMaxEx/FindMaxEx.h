#pragma once
#include "stdafx.h"

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}
	
	auto max = arr[0];
	for (auto& val : arr)
	{
		max = (less(max, val)) ? val : max;
	}

	maxValue = max;
	return true;
}
