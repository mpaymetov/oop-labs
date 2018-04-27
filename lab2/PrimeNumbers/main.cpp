#include "stdafx.h"
#include "PrimeNumbers.h"

constexpr int upperBoundMax = 100000000;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid number of arguments.\n";
		std::cout << "Usage: PrimeNumbers.exe <upperBound 1..10^8>\n";
		return 1;
	}

	std::string str = argv[1];
	int upperBound = 0;
	try
	{
		upperBound = stoi(str);
	}
	catch (const std::out_of_range&)
	{
		std::cout << "Invalid argument.\n";
		std::cout << "Usage: PrimeNumbers.exe <upperBound 1..10^8>\n";
		return 1;
	}
	catch (const std::invalid_argument&)
	{
		std::cout << "Invalid argument.\n";
		std::cout << "Usage: PrimeNumbers.exe <upperBound 1..10^8>\n";
		return 1;
	}

	if (upperBound < 1 || upperBound > upperBoundMax)
	{
		std::cout << "Invalid argument.\n";
		std::cout << "Usage: PrimeNumbers.exe <upperBound 1..10^8>\n";
		return 1;
	}

	std::set<int> primeNumbersSet = GeneratePrimeNumbersSet(upperBound);
	std::cout << "to " << upperBound << " contains " << primeNumbersSet.size() << " prime numbers\n";

	return 0;
}
