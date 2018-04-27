// PrimeNumbers.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

bool GetNumber(const std::string &str, int& number)
{
	try
	{
		number = stoi(str);
	}
	catch (const std::exception& e)
	{
		return false;
	}
	return true;
}

std::vector<bool> GenerateIsPrimeVector(int upperBound)
{
	std::vector<bool> isPrime(upperBound + 1, true);
	for (int number = 2; number * number <= upperBound; ++number)
	{
		if (isPrime[number])
		{
			int step = number * 2;
			if (number == 2)
			{
				step = number;
			}
			for (int numberNotPrime = number * number; numberNotPrime <= upperBound; numberNotPrime += step)
			{
				isPrime[numberNotPrime] = false;
			}
		}
	}
	return isPrime;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<int> primeNumbers;
	std::vector<bool> isPrime = GenerateIsPrimeVector(upperBound);
	for (int number = 2; number <= upperBound; number++)
	{
		if (isPrime[number])
		{
			primeNumbers.emplace_hint(primeNumbers.end(), number);
		}
	}
	return primeNumbers;
}

void PrintPrimeNumbers(const std::set<int>& primeNumbers)
{
	std::copy(primeNumbers.begin(), primeNumbers.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

