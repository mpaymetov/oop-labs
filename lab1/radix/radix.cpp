// radix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int StringToInt(const std::string& str, int radix, bool & wasError)
{
	std::string string = str;
	int number = 0;
	int digit;
	bool isNegative = false;
	if (string.front() == '-')
	{
		isNegative = true;
		string.erase(0, 1);
	}

	for (char& ch : string)
	{
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
		
		if (((INT_MAX - digit) / radix) >= number)
		{
			number = number * radix + digit;
		}
		else
		{
			wasError = true;
			return number;
		}
	}

	if (isNegative)
	{
		number *= -1;
	}
	return number;
}

std::string IntToString(int n, int radix, bool & wasError)
{
	std::string numberStr = "";
	int number = n;
	int digit;
	std::string ch;
	bool isNegative = false;
	if (number < 0)
	{
		isNegative = true;
		number *= -1;
	}

	while(number != 0) 
	{
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

bool getRadix(const std::string& str, int& radix)
{
	try
	{
		radix = std::stoi(str);
	}
	catch (const std::exception & err)
	{
		std::cout << err.what() << std::endl;
		return false;
	}

	if ((radix < 2) || (radix > 36))
	{
		return false;
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
	
	int source_radix, destination_radix;
	if (!getRadix(argv[1], source_radix))
	{
		std::cout << "Invalid source radix" << std::endl;
		return 1;
	}
	if (!getRadix(argv[2], destination_radix))
	{
		std::cout << "Invalid destination radix" << std::endl;
		return 1;
	}

	std::string string_number = argv[3];
	bool wasError = false;
	int numder = StringToInt(string_number, source_radix, wasError);
	if (wasError)
	{
		std::cout << "Invalid argument\n";
		return 1;
	}
	
	std::cout << IntToString(numder, destination_radix, wasError) << "\n";	
	return 0;
}
