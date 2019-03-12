#include "stdafx.h"
#include "dictionary.h"

void InsertToDictionary(Dictionary& dictionary, const std::string& originalWord, const std::string& translation)
{
	dictionary.forward.insert(std::pair<std::string, std::string>(originalWord, translation));
	dictionary.reverse.insert(std::pair<std::string, std::string>(translation, originalWord));
}

bool FindInDictionary(Dictionary& dictionary, const std::string& originalWord, std::string& translation)
{
	translation = "";
	for (DictionaryMap::iterator it = dictionary.forward.equal_range(originalWord).first; it != dictionary.forward.equal_range(originalWord).second; ++it)
	{
		translation += it->second + " ";
	}
	for (DictionaryMap::iterator it = dictionary.reverse.equal_range(originalWord).first; it != dictionary.reverse.equal_range(originalWord).second; ++it)
	{
		translation += it->second + " ";
	}

	if (translation == "")
	{
		return false;
	}
	return true;
}

void ReadDictionaryFromStream(std::istream& input, Dictionary& dictionary)
{
	std::string word, translation;
	while (!input.eof())
	{
		std::getline(input, word);
		if (!input.eof())
		{
			std::getline(input, translation);
			InsertToDictionary(dictionary, word, translation);
		}
	}
	return;
}

void ReadDictionaryFromFile(const std::string& inputFileName, Dictionary& dictionary)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName);	
	if (!inputFile.is_open())
	{
		std::cout << "Input file can`t open\n";
		return;
	}
	ReadDictionaryFromStream(inputFile, dictionary);
	return;
}

void SaveDictionaryToStream(std::ostream& output, Dictionary& dictionary)
{
	for (DictionaryMap::iterator it = dictionary.forward.begin(); it != dictionary.forward.end(); ++it)
	{
		output << (*it).first << std::endl << (*it).second << std::endl;
	}
}

void SaveDictionaryToFile(const std::string &outputFileName, Dictionary& dictionary)
{
	std::ofstream outputFile;
	outputFile.open(outputFileName);
	if (!outputFile.is_open())
	{
		std::cout << "Output file can`t open\n";
		return;
	}
	SaveDictionaryToStream(outputFile, dictionary);
	std::cout << "Изменения сохранены. До свидания.\n";
}

