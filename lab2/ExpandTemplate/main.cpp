#include "stdafx.h"
#include "ExpandTemplate.h"

bool ExpandTemplateFile(std::string& inputFileName, std::string& outputFileName, std::map<std::string, std::string> const& params)
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

	std::string str;
	while (std::getline(inputFile, str))
	{
		outputFile << ExpandTemplate(str, params) << std::endl;
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		std::cout << "Invalid number of arguments.\n";
		std::cout << "Usage: expand_template.exe <input - file> <output - file>[<param> <value>[<param> <value> …]]\n";
		return 1;
	}

	std::string inputFileName = argv[1];
	std::string outputFileName = argv[2];

	std::map<std::string, std::string> params;
	for (int i = 3; i + 2 <= argc; i += 2)
	{
		std::string search = argv[i];
		std::string replace = argv[i + 1];
		params[search] = replace;
	}

	if (!ExpandTemplateFile(inputFileName, outputFileName, params))
	{
		return 1;
	}
	
	return 0;
}
