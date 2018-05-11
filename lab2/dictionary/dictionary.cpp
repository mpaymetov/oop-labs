#include "stdafx.h"

typedef std::multimap<std::string, std::string> DictionaryType;

void InsertToDyctionary(DictionaryType &dyctionary, DictionaryType &reverseDyctionary, const std::string &originalWord, const std::string &translation)
{
	dyctionary.insert(std::pair<std::string, std::string>(originalWord, translation));
	reverseDyctionary.insert(std::pair<std::string, std::string>(translation, originalWord));
}

bool FindInDyctionary(DictionaryType &dyctionary, DictionaryType &reverseDyctionary, const std::string &originalWord, std::string &translation)
{
	translation = "";
	if (dyctionary.find(originalWord) != dyctionary.end())
	{
		DictionaryType::iterator it;
		for (it = dyctionary.equal_range(originalWord).first; it != dyctionary.equal_range(originalWord).second; ++it)
		{
			translation += it->second + " ";
		}
		return true;
	}
	else if (reverseDyctionary.find(originalWord) != reverseDyctionary.end())
	{
		DictionaryType::iterator it;
		for (it = reverseDyctionary.equal_range(originalWord).first; it != reverseDyctionary.equal_range(originalWord).second; ++it)
		{
			translation += it->second + " ";
		}
		return true;
	}
	else
	{
		return false;
	}
}

void ReadDyctionaryFromFile(const std::string &inputFileName, DictionaryType &dyctionary, DictionaryType &reverseDyctionary)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName);	
	if (!inputFile.is_open())
	{
		std::cout << "Input file can`t open\n";
		return;
	}
	std::string originalWord, translation;
	while (!inputFile.eof())
	{
		std::getline(inputFile, originalWord);
		if (!inputFile.eof())
		{
			std::getline(inputFile, translation);
			InsertToDyctionary(dyctionary, reverseDyctionary, originalWord, translation);
		}
	}
	inputFile.close();
}

void SaveDyctionaryToFile(const std::string &outputFileName, DictionaryType &dyctionary)
{
	std::ofstream outputFile;
	outputFile.open(outputFileName);
	if (!outputFile.is_open())
	{
		std::cout << "Output file can`t open\n";
		return;
	}
	for (DictionaryType::iterator it = dyctionary.begin(); it != dyctionary.end(); ++it)
	{
		outputFile << (*it).first << std::endl << (*it).second << std::endl;
	}
	std::cout << "Изменения сохранены. До свидания.\n";
	outputFile.close();
}

