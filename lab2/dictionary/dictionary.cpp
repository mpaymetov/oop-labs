#include "stdafx.h"
#include "dictionary.h"

void InsertToDictionary(Dictionary& dictionary, const std::string& original, const std::string& translation)
{
	std::string originalWord = original;
	std::transform(originalWord.begin(), originalWord.end(), originalWord.begin(), ::tolower);
	std::string translationWord = translation;
	std::transform(translationWord.begin(), translationWord.end(), translationWord.begin(), ::tolower);
	dictionary.forward.insert(std::pair<std::string, std::string>(originalWord, translationWord));
	dictionary.reverse.insert(std::pair<std::string, std::string>(translationWord, originalWord));
}

bool FindInDictionary(const Dictionary& dictionary, const std::string& originalWord, std::string& translation)
{
	std::string word = originalWord;
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);
	translation = "";
	for (auto it = dictionary.forward.equal_range(word).first; it != dictionary.forward.equal_range(word).second; ++it)
	{
		translation += it->second + " ";
	}
	for (auto it = dictionary.reverse.equal_range(word).first; it != dictionary.reverse.equal_range(word).second; ++it)
	{
		translation += it->second + " ";
	}

	if (translation == "")
	{
		return false;
	}
	return true;
}

Dictionary ReadDictionaryFromStream(std::istream& input)
{
	Dictionary dictionary;
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
	return dictionary;
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
	dictionary = ReadDictionaryFromStream(inputFile);
	return;
}

void SaveDictionaryToStream(std::ostream& output, const Dictionary& dictionary)
{
	for (const auto& [word, translation] : dictionary.forward)
	{
		output << word << std::endl << translation << std::endl;
	}
}

void SaveDictionaryToFile(const std::string &outputFileName, const Dictionary& dictionary)
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

