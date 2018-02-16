// flipbyte.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		std::cout << "invalid argument count\n"
			<< "usage: flipbyte.exe <byte>";
		return 1;
	}

	
	unsigned int inputByte = std::stoi(argv[1]);
	int outputByte = 0;

	for (int i = 0; i < 7; i++)
	{
		outputByte = inputByte & 0x01 | outputByte;
		inputByte >>= 1;
		outputByte <<= 1;
	}

	std::cout << outputByte << "\n";

    return 0;
}

