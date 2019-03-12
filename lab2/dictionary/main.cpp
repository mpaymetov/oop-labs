#include "stdafx.h"
#include "dictionary.h"

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
	std::string inputString, translate;
	do
	{
		std::cout << ">";
		std::getline(std::cin, inputString);
		if ((std::cin.eof()) || (inputString == "..."))
		{
			break;
		}

		std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
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
				std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
				InsertToDictionary(dictionary, inputString, translate);
				isChanged = true;
			}
			else
			{
				std::cout << "Слово “" << inputString << "” проигнорировано.\n";
			}
		}
	} while (true);

	if (isChanged) 
	{
		std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.";
		std::cin >> inputString;
		if ((inputString == "y") || (inputString == "Y"))
		{
			if (fileName == "")
			{
				std::cout << "Введите имя файла для сохранения: ";
				std::cin >> fileName;
			}
			SaveDictionaryToFile(fileName, dictionary);
		}
	}
	return 0;
}

