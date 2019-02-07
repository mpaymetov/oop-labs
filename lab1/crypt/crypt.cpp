// crypt.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

bool CryptFile(const std::string inputFileName, const std::string outputFileName, const uint8_t key)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName, std::ifstream::binary);

	std::ofstream outputFile;
	outputFile.open(outputFileName);

	if (!inputFile.is_open())
	{
		std::cout << "Input file can`t open\n";
		return false;
	}

	uint8_t byte;
	while (inputFile.read(reinterpret_cast<char*>(&byte), 1))
	{
		byte = byte ^ key;
		byte = byte & 0b10000000 >> 2 | byte & 0b01000000 >> 5 | byte & 0b00100000 >> 5 | byte & 0b00010000 << 3 |
			byte & 0b00001000 << 3 | byte & 0b00000100 << 2 | byte & 0b00000010 << 2 | byte & 0b00000001 << 2;
		outputFile.put(byte);
	}
	outputFile.flush();
	return true;
}

bool DecryptFile(const std::string inputFileName, const std::string outputFileName, const uint8_t key)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName, std::ifstream::binary);

	std::ofstream outputFile;
	outputFile.open(outputFileName);

	if (!inputFile.is_open())
	{
		std::cout << "Input file can`t open\n";
		return false;
	}

	uint8_t byte;
	while (inputFile.read(reinterpret_cast<char*>(&byte), 1))
	{
		byte = byte & 0b10000000 >> 3 | byte & 0b01000000 >> 3 | byte & 0b00100000 << 2 | byte & 0b00010000 >> 2 |
			byte & 0b00001000 >> 2 | byte & 0b00000100 >> 2 | byte & 0b00000010 << 5 | byte & 0b00000001 << 5;
		byte = byte ^ key;
		outputFile.put(byte);
	}
	outputFile.flush();
	return true;
}

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		std::cout << "invalid argument count\n" 
			<< "usage: crypt.exe crypt <input file> <output file> <key>\n"
			<< "or: crypt.exe decrypt <input file> <output file> <key>\n";
		return 1;
	}

	uint8_t key;
	int checkKey = std::stoi(argv[4]);
	if (checkKey < 0 || checkKey > 255)
	{
		std::cout << "Key is not in byte range.\n";
		return 1;
	}
	else
	{
		key = static_cast<uint8_t>(checkKey);
	}

	std::string mode = argv[1];

	if (mode == "crypt")
	{
		if (!CryptFile(argv[2], argv[3], key))
		{
			std::cout << "File crypt error.\n";
			return 1;
		}
	}
	else if (mode == "decrypt")
	{
		if (!DecryptFile(argv[2], argv[3], key))
		{
			std::cout << "File decrypt error.\n";
			return 1;
		}
	}
	else
	{
		std::cout << "invalid crypt/decrypt argument\n";
		return 1;
	}

    return 0;
}

