// calcbits.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

uint8_t CalcBits(const uint8_t byte)
{
	uint8_t bits = (byte & 0b00000001) + ((byte & 0b00000010) >> 1) + ((byte & 0b00000100) >> 2) + ((byte & 0b00001000) >> 3) 
		+ ((byte & 0b00010000) >> 4) + ((byte & 0b00100000) >> 5) + ((byte & 0b01000000) >> 6) + ((byte & 0b10000000) >> 7);
	return bits;
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		std::cout << "invalid argument count\n"
			<< "usage: calcbits.exe <byte>\n";
		return 1;
	}

	try
	{
		int byte = std::stoi(argv[1]);
		if (byte < 0 || byte > 255)
		{
			std::cout << "Input number is not in byte range.\n";
			return 1;
		}
		std::cout << static_cast<int>(CalcBits(static_cast<uint8_t>(byte))) << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << "!Error:" << e.what() << "!\n";
		return 1;
	}

    return 0;
}

