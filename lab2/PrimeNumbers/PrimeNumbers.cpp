// PrimeNumbers.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

bool GetNumber(const std::string &str, int number)
{
	try
	{
		number = stoi(str);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl; 
		return false;
	}
	const int upperBoundMax = 100000000;
	if (number < 1 || number > upperBoundMax)
	{
		return false;
	}
	return true;
}

std::vector<bool> GeneratePrimeNumbersVector(int upperBound)
{
	std::vector<bool> primeNumbersVector(upperBound + 1, true);
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
			primeNumbers.emplace_hint(primeNumbers.end(), number);
		}
	}
	return primeNumbers;
}
