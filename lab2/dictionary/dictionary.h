#pragma once

typedef std::multimap<std::string, std::string> DictionaryMap;

struct Dictionary
{
	DictionaryMap forward;
	DictionaryMap reverse;
};

void InsertToDictionary(Dictionary& dictionary, const std::string& originalWord, const std::string& translation);

bool FindInDictionary(const Dictionary& dictionary, const std::string& originalWord, std::string& translation);

Dictionary ReadDictionaryFromStream(std::istream& input);

void ReadDictionaryFromFile(const std::string& inputFileName, Dictionary& dictionary);

void SaveDictionaryToStream(std::ostream& output, const Dictionary& dictionary);

void SaveDictionaryToFile(const std::string& outputFileName, const Dictionary& dictionary);

