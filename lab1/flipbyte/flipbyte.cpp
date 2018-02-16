// flipbyte.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

uint8_t FlipByte(uint8_t byte)
{
	uint8_t outputByte = 0;
	uint8_t inputByte = byte;

	for (int i = 0; i < 8; i++)
	{
		outputByte <<= 1; 
		outputByte = inputByte & 0x01 | outputByte;
		inputByte >>= 1;
		
	}

	return outputByte;
}


int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		std::cout << "invalid argument count\n"
			<< "usage: flipbyte.exe <byte>";
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
		std::cout << static_cast<int>(FlipByte(static_cast<uint8_t>(byte))) << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << "!Error:" << e.what() << "!\n";
		return 1;
	}

	return 0;
}

