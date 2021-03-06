// crypt.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
typedef void(*CryptFunction)(uint8_t& byte, const uint8_t key);

void CryptByte(uint8_t& byte, const uint8_t key)
{
	byte = byte ^ key;
	byte = byte & 0b10000000 >> 2 | byte & 0b01000000 >> 5 | byte & 0b00100000 >> 5 | byte & 0b00010000 << 3 |
		byte & 0b00001000 << 3 | byte & 0b00000100 << 2 | byte & 0b00000010 << 2 | byte & 0b00000001 << 2;
	return;
}

void DecryptByte(uint8_t& byte, const uint8_t key)
{
	byte = byte & 0b10000000 >> 3 | byte & 0b01000000 >> 3 | byte & 0b00100000 << 2 | byte & 0b00010000 >> 2 |
			byte & 0b00001000 >> 2 | byte & 0b00000100 >> 2 | byte & 0b00000010 << 5 | byte & 0b00000001 << 5;
	byte = byte ^ key;
	return;
}

void TransformFileContent(std::ifstream& inputFile, std::ofstream &outputFile, CryptFunction cryptFunction, const uint8_t key)
{
	uint8_t byte;
	while (inputFile.read(reinterpret_cast<char*>(&byte), 1))
	{
		cryptFunction(byte, key);
		outputFile.put(byte);
	}
	return;
}

bool GetKeyFromString(const std::string & Str, uint8_t & key)
{
	int intKey;
	try
	{
		intKey = std::stoi(Str);
	}
	catch (const std::exception & err)
	{
		std::cout << err.what() << std::endl;
		return false;
	}

	if (intKey < 0 || intKey > 255)
	{
		std::cout << "Key is not in byte range.\n";
		return false;
	}
	else
	{
		key = static_cast<uint8_t>(intKey);
	}

	return true;
}

bool CryptFile(const std::string& cryptMode, const std::string& inputFileName, const std::string& outputFileName, const std::string& keyStr)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName, std::ifstream::binary);
	if (!inputFile.is_open())
	{
		std::cout << "Input file can`t open\n";
		return false;
	}

	std::ofstream outputFile;
	outputFile.open(outputFileName, std::ofstream::binary);
	if (!outputFile.is_open())
	{
		std::cout << "Output file can`t open\n";
		return false;
	}

	uint8_t key;
	if (!GetKeyFromString(keyStr, key))
	{
		std::cout << "invalid key argument\n";
		return false;
	}

	if (cryptMode == "crypt")
	{
		TransformFileContent(inputFile, outputFile, CryptByte, key);
	}
	else if (cryptMode == "decrypt")
	{
		TransformFileContent(inputFile, outputFile, DecryptByte, key);
	}
	else
	{
		std::cout << "invalid crypt/decrypt argument\n";
		return false;
	}

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

	std::string cryptMode = argv[1];
	std::string inputFileName = argv[2];
	std::string outputFileName = argv[3];
	std::string keyStr = argv[4];
	
	return CryptFile(cryptMode, inputFileName, outputFileName, keyStr) ? 0 : 1;
}

