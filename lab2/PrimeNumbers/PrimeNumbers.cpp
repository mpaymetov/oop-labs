// PrimeNumbers.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

std::vector<bool> GeneratePrimeNumbersVector(int upperBound)
{
	std::vector<bool> primeNumbersVector(upperBound + 1, true);
	primeNumbersVector[0] = false;
	primeNumbersVector[1] = true;
	for (int number = 2; number * number <= upperBound; ++number)
	{
		if (primeNumbersVector[number])
		{
			for (int numberNotPrime = number * 2; numberNotPrime <= upperBound; numberNotPrime += number)
			{
				primeNumbersVector[numberNotPrime] = false;
			}
		}
	}
	return primeNumbersVector;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<int> primeNumbers;
	std::vector<bool> primeNumbersVector = GeneratePrimeNumbersVector(upperBound);
	for (int number = 2; number <= upperBound; number++)
	{
		if (primeNumbersVector[number])
		{
			primeNumbers.emplace(number);
		}
	}
	return primeNumbers;
}
