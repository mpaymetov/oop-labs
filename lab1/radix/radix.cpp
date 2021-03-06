// radix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int StringToInt(std::string string, const unsigned int& radix, bool & isNegative, bool & wasError)
{
	unsigned int number = 0;
	if (string.front() == '-')
	{
		isNegative = true;
		string.erase(0, 1);
	}

	for (char& ch : string)
	{
		unsigned int digit;
		if ((ch >= '0') && (ch <= '9'))
		{
			digit = ch - '0';
		}
		else if ((ch >= 'A') && (ch <= 'Z'))
		{
			digit = ch - 'A' + 10;
		}
		else
		{
			wasError = true;
			return number;
		}

		if (digit >= radix)
		{
			wasError = true;
			return number;
		}
		
		if (((UINT_MAX - digit) / radix) >= number)
		{
			number = number * radix + digit;
		}
		else
		{
			wasError = true;
			return number;
		}
	}

	return number;
}

std::string IntToString(unsigned int number, unsigned int radix, bool isNegative, bool & wasError)
{
	std::string numberStr = "";
	if (number == 0)
	{
		numberStr = "0";
	}

	while(number != 0) 
	{
		int digit;
		std::string ch;
		digit = number % radix;
		if (digit > 9)
		{
			ch = 'A' + digit - 10;
		}
		else
		{
			ch = '0' + digit;
		}
		numberStr = ch + numberStr;
		number = (number - digit) / radix;
	}

	if (isNegative)
	{
		numberStr = '-' + numberStr;
	}
	return numberStr;
}

bool GetRadix(const std::string& str, unsigned int& radix)
{
	int radixInt;
	try
	{
		radixInt = std::stoi(str);
	}
	catch (const std::exception & err)
	{
		std::cout << err.what() << std::endl;
		return false;
	}

	if ((radixInt < 2) || (radixInt > 36))
	{
		return false;
	}
	else
	{
		radix = (unsigned int)radixInt;
	}
	return true;
}


int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}
	
	unsigned int sourceRadix, destinationRadix;
	if (!GetRadix(argv[1], sourceRadix))
	{
		std::cout << "Invalid source radix" << std::endl;
		return 1;
	}
	if (!GetRadix(argv[2], destinationRadix))
	{
		std::cout << "Invalid destination radix" << std::endl;
		return 1;
	}

	std::string stringNumber = argv[3];
	bool isNegative = false;
	bool wasError = false;
	unsigned int numder = StringToInt(stringNumber, sourceRadix, isNegative, wasError);
	if (wasError)
	{
		std::cout << "Invalid argument\n";
		return 1;
	}
	
	std::cout << IntToString(numder, destinationRadix, isNegative, wasError) << "\n";
	return 0;
}
