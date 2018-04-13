#include "stdafx.h"
#include "../vector/vector.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>

bool IsEqually(const std::vector <double>& array1, const std::vector <double>& array2)
{
	return array1 == array2;
}

TEST_CASE("ProcessVector produces empty vector from empty vector")
{
	std::vector<double> number = {};
	ProcessVector(number);
	REQUIRE(IsEqually(number, {}));
}

TEST_CASE("ProcessVector divides each element by half of the maximum element")
{
	std::vector<double> number = {2, 2, 4};
	ProcessVector(number);
	REQUIRE(IsEqually(number, {1, 1, 2}));
}

TEST_CASE("ProcessVector does not change vector if the maximum element is 0")
{
	std::vector<double> number = { -4, -2, 0 };
	ProcessVector(number);
	REQUIRE(IsEqually(number, { -4, -2, 0 }));
}

