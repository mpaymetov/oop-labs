// radix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int StringToInt(const std::string& str, int radix, bool & wasError)
{
	std::string string = str;
	int number = 0;
	int digit;

	for (char& c : string) {
		digit = c - '0';
		if (digit > 9)
		{
			digit = c - 'A' + 10;
		}
		if (digit >= radix)
		{
			wasError = true;
		}
		number = number * radix + digit;
	}
	return number;
}

std::string IntToString(int n, int radix, bool & wasError)
{
	std::string number = std::to_string(n);

	return number;
}


int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	int source_radix = std::stoi(argv[1]);
	int destination_radix = std::stoi(argv[2]);
	std::string string_number = argv[3];

	bool wasError = false;
	int numder = StringToInt(string_number, source_radix, wasError);
	std::cout << IntToString(numder, destination_radix, wasError) << "\n";	
	return 0;
}

