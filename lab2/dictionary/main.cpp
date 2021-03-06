#include "stdafx.h"
#include "dictionary.h"

void ProcessWord(const std::string& inputString, Dictionary& dictionary, bool& isChanged)
{
	std::string translate;
	if (FindInDictionary(dictionary, inputString, translate))
	{
		std::cout << translate << "\n";
	}
	else
	{
		std::cout << "Неизвестное слово “" << inputString << "”. Введите перевод или пустую строку для отказа.\n";
		std::getline(std::cin, translate);
		if (translate != "")
		{
			InsertToDictionary(dictionary, inputString, translate);
			isChanged = true;
		}
		else
		{
			std::cout << "Слово “" << inputString << "” проигнорировано.\n";
		}
	}
}

void OfferSaveDictionaryToFile(std::string& fileName, const Dictionary& dictionary)
{
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.";
	std::string answer;
	std::cin >> answer;
	if ((answer == "y") || (answer == "Y"))
	{
		if (fileName == "")
		{
			std::cout << "Введите имя файла для сохранения: ";
			std::cin >> fileName;
		}
		SaveDictionaryToFile(fileName, dictionary);
	}
}

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Dictionary dictionary;
	std::string fileName;
	if (argc >= 2)
	{
		fileName = argv[1];
		ReadDictionaryFromFile(fileName, dictionary);
	}
	
	bool isChanged = false;
	std::string inputString;
	do
	{
		std::cout << ">";
		std::getline(std::cin, inputString);
		if ((std::cin.eof()) || (inputString == "..."))
		{
			break;
		}
		ProcessWord(inputString, dictionary, isChanged);
	} while (true);

	if (isChanged)
	{
		OfferSaveDictionaryToFile(fileName, dictionary);
	}
	return 0;
}

