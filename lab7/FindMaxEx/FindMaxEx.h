#pragma once
#include "stdafx.h"

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}
	
	auto max = arr.begin();
	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		max = (less(*max, *it)) ? it : max;
	}

	maxValue = *max;
	return true;
}
