// Replace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString == "")
	{
		return subject;
	}

	size_t pos = 0;
	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos != std::string::npos) 
		{
			result.append(replacementString);
			pos = foundPos + searchString.length();
		}
		else
		{
			break;
		}
	}
	return result;
}

void CopyFileWithReplace(std::istream& input, std::ostream& output, const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

bool CopyFileWithReplace(const std::string& inputFileName, const std::string& outputFileName, const std::string& searchString, const std::string& replacementString)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "Can not open input file\n";
		return false;
	}
	
	std::ofstream outputFile;
	outputFile.open(outputFileName);
	if (!outputFile.is_open())
	{
		std::cout << "Can not open output file\n";
		return false;
	}

	CopyFileWithReplace(inputFile, outputFile, searchString, replacementString);
	if (!outputFile.flush())
	{
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	std::string inputFileName = argv[1];
	std::string outputFileName = argv[2];
	std::string search = argv[3];
	std::string replace = argv[4];

	if (!CopyFileWithReplace(inputFileName, outputFileName, search, replace))
	{
		return 1;
	}

	return 0;
}
