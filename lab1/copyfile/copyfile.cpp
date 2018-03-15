// copyfile.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

bool CopyFile(std::string inputFileName, std::string outputFileName)
{
	bool answer = true;
	
	std::ifstream inputFile;
	inputFile.open(inputFileName);

	std::ofstream outputFile;
	outputFile.open(outputFileName);
	
	if (!inputFile.is_open())
	{
		std::cout << "Input file can`t open\n";
		answer = false;
	}

	/*if (!outputFile.is_open())
	{
		std::cout << "Output file can`t open\n";
		ans = false;
	}*/

	char ch;
	while (inputFile.get(ch))
	{
		outputFile.put(ch);
		//std::cout << ch;
		//std::cout << "\n";
	}

	outputFile.flush();
	outputFile.close();
	inputFile.close();

	return answer;
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

