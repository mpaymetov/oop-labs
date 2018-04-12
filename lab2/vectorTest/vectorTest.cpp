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

TEST_CASE("input - empty vector, output - empty vector")
{
	std::vector<double> number = {};
	ProcessVector(number);
	REQUIRE(IsEqually(number, {}));
}

TEST_CASE("input - not empty vector, output - not empty vector")
{
	std::vector<double> number = {2, 2, 4};
	ProcessVector(number);
	REQUIRE(IsEqually(number, {1, 1, 2}));
}

TEST_CASE("input - maximum is 0, output - not change")
{
	std::vector<double> number = { -4, -2, 0 };
	ProcessVector(number);
	REQUIRE(IsEqually(number, { -4, -2, 0 }));
}

TEST_CASE("input - not empty vector, output - sorted")
{
	std::vector<double> number = { 4, 1, 2 };
	ProcessVector(number);
	REQUIRE(IsEqually(number, { 0.5, 1, 2 }));
}
