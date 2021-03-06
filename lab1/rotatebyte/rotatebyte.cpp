// rotatebyte.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

uint8_t RotateByteLeft(uint8_t byte, uint8_t numbOfBits)
{
	uint8_t outputByte = byte;
	for (int i = 0; i < numbOfBits; i++)
	{
		outputByte = outputByte << 1 | outputByte >> 7;
	}
	return outputByte;
}

uint8_t RotateByteRight(uint8_t byte, uint8_t numbOfBits)
{
	uint8_t outputByte = byte;
	for (int i = 0; i < numbOfBits; i++)
	{
		outputByte = outputByte >> 1 | outputByte << 7;
	}
	return outputByte;
}

int main(int argc, char * argv[])
{
	if (argc != 4)
	{
		std::cout << "invalid argument count\n"
			<< "usage: rotatebyte.exe <byte> <numb of bits> <L / R>\n";
		return 1;
	}

	int byte;
	int numbOfBits;
	std::string rotateType = argv[3];

	try
	{
		byte = std::stoi(argv[1]);
		if (byte < 0 || byte > 255)
		{
			std::cout << "Input number is not in byte range.\n";
			return 1;
		}
		
	}
	catch (const std::exception& e)
	{
		std::cout << "!Error:" << e.what() << "!\n";
		return 1;
	}

	try
	{
		numbOfBits = std::stoi(argv[2]);
		if (numbOfBits < 0 || numbOfBits > 255)
		{
			std::cout << "Input number of bits is not in byte range.\n";
			return 1;
		}

	}
	catch (const std::exception& e)
	{
		std::cout << "!Error:" << e.what() << "!\n";
		return 1;
	}

	if (rotateType == "L")
	{
		std::cout << static_cast<int>(RotateByteLeft(static_cast<uint8_t>(byte), static_cast<uint8_t>(numbOfBits))) << "\n";
	}
	else
	{
		if (rotateType == "R")
		{
			std::cout << static_cast<int>(RotateByteRight(static_cast<uint8_t>(byte), static_cast<uint8_t>(numbOfBits))) << "\n";
		}
		else
		{
			std::cout << "Rotate type is not valid.\n";
			return 1;
		}
	}	

	return 0;
}

