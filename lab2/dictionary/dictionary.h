#pragma once

typedef std::multimap<std::string, std::string> DictionaryMap;

struct Dictionary
{
	DictionaryMap forward;
	DictionaryMap reverse;
};

void InsertToDictionary(Dictionary& dictionary, const std::string& originalWord, const std::string& translation);

bool FindInDictionary(Dictionary& dictionary, const std::string& originalWord, std::string& translation);

void ReadDictionaryFromStream(std::istream& input, Dictionary& dictionary);

void ReadDictionaryFromFile(const std::string& inputFileName, Dictionary& dictionary);

void SaveDictionaryToStream(std::ostream& output, Dictionary& dictionary);

void SaveDictionaryToFile(const std::string& outputFileName, Dictionary& dictionary);

