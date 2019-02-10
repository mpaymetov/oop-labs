// Replace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	size_t pos = 0;
	std::string result = subject;
	while (pos < result.length())
	{
		size_t foundPos = result.find(searchString, pos);		
		if (foundPos != std::string::npos) 
		{
			result.replace(foundPos, searchString.length(), replacementString);
			pos = foundPos + replacementString.length();
		}
		else
		{
			break;
		}
	}
	return result;
}

void CopyFileWithReplace(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	std::ifstream inputFile;
	inputFile.open(argv[1]);

	std::ofstream outputFile;
	outputFile.open(argv[2]);

	std::string search = argv[3];
	std::string replace = argv[4];

	CopyFileWithReplace(inputFile, outputFile, search, replace);
	outputFile.flush();

	return 0;
}
