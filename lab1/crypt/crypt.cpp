// crypt.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

bool CryptFile(const std::string inputFileName, const std::string outputFileName, const uint8_t key)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName);

	std::ofstream outputFile;
	outputFile.open(outputFileName);

	if (!inputFile.is_open())
	{
		std::cout << "Input file can`t open\n";
		return false;
	}

	char ch;
	while (inputFile.get(ch))
	{
		ch = ch ^ key;
		ch = ch & 0b10000000 >> 2 | ch & 0b01000000 >> 5 | ch & 0b00100000 >> 5 | ch & 0b00010000 << 3 |
			ch & 0b00001000 << 3 | ch & 0b00000100 << 2 | ch & 0b00000010 << 2 | ch & 0b00000001 << 2;
		outputFile.put(ch);
	}
	outputFile.flush();
	return true;
}

bool DecryptFile(const std::string inputFileName, const std::string outputFileName, const uint8_t key)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName);

	std::ofstream outputFile;
	outputFile.open(outputFileName);

	if (!inputFile.is_open())
	{
		std::cout << "Input file can`t open\n";
		return false;
	}

	char ch;
	while (inputFile.get(ch))
	{
		ch = ch & 0b10000000 << 2 | ch & 0b01000000 << 5 | ch & 0b00100000 << 5 | ch & 0b00010000 >> 3 |
			ch & 0b00001000 >> 3 | ch & 0b00000100 >> 2 | ch & 0b00000010 >> 2 | ch & 0b00000001 >> 2;
		ch = ch ^ key;
		outputFile.put(ch);
	}
	outputFile.flush();
	return true;
}

int main(int argc, char * argv[])
{
	std::cout << "'" << argv[1] << "'\n" << "'" << argv[2] << "'\n" << "'" << argv[3] << "'\n" << "'" << argv[4] << "'\n";
	if (argc != 5)
	{
		std::cout << "invalid argument count\n" 
			<< "usage: crypt.exe crypt <input file> <output file> <key>\n"
			<< "or: crypt.exe decrypt <input file> <output file> <key>\n";
		return 1;
	}

	uint8_t key = std::stoi(argv[4]);
	if (key < 0 || key > 255)
	{
		std::cout << "Key is not in byte range.\n";
		return 1;
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

