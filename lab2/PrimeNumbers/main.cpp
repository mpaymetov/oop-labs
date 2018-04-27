#include "stdafx.h"
#include "PrimeNumbers.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid number of arguments.\n";
		std::cout << "Usage: PrimeNumbers.exe <upperBound 1..10^8>\n";
		return 1;
	}

	int upperBound = 0;
	if (!GetNumber(argv[1], upperBound))
	{
		std::cout << "Invalid argument.\n";
		std::cout << "Usage: PrimeNumbers.exe <upperBound 1..10^8>\n";
		return 1;
	}

	const int upperBoundMax = 100000000;
	if (upperBound < 1 || upperBound > upperBoundMax)
	{
		std::cout << "Invalid argument.\n";
		std::cout << "Usage: PrimeNumbers.exe <upperBound 1..10^8>\n";
		return 1;
	}

	std::set<int> primeNumbersSet = {};
	#ifndef _DEBUG
		primeNumbersSet = GeneratePrimeNumbersSet(upperBound);
	#endif
	std::cout << "to " << upperBound << " contains " << primeNumbersSet.size() << " prime numbers:\n";
	PrintPrimeNumbers(primeNumbersSet);
	return 0;
}
