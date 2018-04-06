#include "stdafx.h"
#include "../vector/vector.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>

bool IsEqually(const std::vector <float>& array1, const std::vector <float>& array2)
{
	return array1 == array2;
}

TEST_CASE("input - empty vector, output - empty vector")
{
	std::vector<float> number = {};
	ProcessVector(number);
	REQUIRE(IsEqually(number, {}));
}

TEST_CASE("input - not empty vector, output - not empty vector")
{
	std::vector<float> number = {2, 2, 4};
	ProcessVector(number);
	REQUIRE(IsEqually(number, {1, 1, 2}));
}

TEST_CASE("input - maximum is 0, output - not change")
{
	std::vector<float> number = { -2, 0, -4 };
	ProcessVector(number);
	REQUIRE(IsEqually(number, { -2, 0, -4 }));
}
