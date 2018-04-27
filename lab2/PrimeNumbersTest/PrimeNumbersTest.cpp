#include "stdafx.h"
#include "../PrimeNumbers/PrimeNumbers.h"

bool IsEqually(const std::set<int>& set1, const std::set<int>& set2)
{
	return set1 == set2;
}

TEST_CASE("test GetNumber - function convert string to int in range 1..10^8 and return bool value")
{
	int number = 0;
	CHECK(GetNumber("", number) == false);
	CHECK(GetNumber("0", number) == false);
	CHECK(GetNumber("1", number) == true);
	CHECK(GetNumber("100000000", number) == true);
	CHECK(GetNumber("100000001", number) == false);
	CHECK(GetNumber("number", number) == false);
}

TEST_CASE("test GeneratePrimeNumbersSet - function return set of prime numbers by lower input number")
{
	CHECK(IsEqually(GeneratePrimeNumbersSet(10), { 2, 3, 5, 7 }));
	CHECK(IsEqually(GeneratePrimeNumbersSet(2), { 2 }));
	CHECK(IsEqually(GeneratePrimeNumbersSet(1), {}));
	CHECK(GeneratePrimeNumbersSet(100000000).size() == 5761455);
}

