#pragma once

typedef std::multimap<std::string, std::string> DictionaryType;

void InsertToDyctionary(DictionaryType &dyctionary, DictionaryType &reverseDyctionary, const std::string &word, const std::string &translation);

bool FindInDyctionary(DictionaryType &dyctionary, DictionaryType &reverseDyctionary, const std::string &originalWord, std::string &translation);

void ReadDyctionaryFromFile(const std::string &inputFileName, DictionaryType &dyctionary, DictionaryType &reverseDyctionary);

void SaveDyctionaryToFile(const std::string &outputFileName, DictionaryType &dyctionary);

