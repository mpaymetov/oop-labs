// copyfile.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

bool CopyFile(const std::string& inputFileName, const std::string& outputFileName)
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
		outputFile.put(ch);
	}

	outputFile.flush();
	
	return true;
}

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		std::cout << "invalid argument count\n"
			<< "usage: copyfile.exe <inputFile> <outputFile>\n";
		return 1;
	}

	if (!CopyFile(argv[1], argv[2]))
	{
		std::cout << "coping file error\n";
		return 1;
	}

    return 0;
}

