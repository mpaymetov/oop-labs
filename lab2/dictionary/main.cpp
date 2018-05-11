#include "stdafx.h"
#include "dictionary.h"

typedef std::multimap<std::string, std::string> DictionaryType;

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	DictionaryType dyctionary, reverseDyctionary;
	std::string fileName = "";
	if (argc >= 2)
	{
		fileName = argv[1];
		ReadDyctionaryFromFile(fileName, dyctionary, reverseDyctionary);
	}
	
	bool isChanged = false;
	std::string inputString = "", translate;
	do
	{
		std::cout << ">";
		std::getline(std::cin, inputString);
		if (inputString == "...")
		{
			break;
		}
		std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
		if (FindInDyctionary(dyctionary, reverseDyctionary, inputString, translate))
		{
			std::cout << translate << "\n";
		}
		else
		{
			std::cout << "Неизвестное слово “" << inputString << "”.Введите перевод или пустую строку для отказа." << "\n";
			std::getline(std::cin, translate);
			if (translate != "")
			{

				std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
				InsertToDyctionary(dyctionary, reverseDyctionary, inputString, translate);
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
				std::cout << "Введите имя файла для сохранения: \n";
				std::cin >> fileName;
				fileName += ".txt";
			}
			SaveDyctionaryToFile(fileName, dyctionary);
		}
	}
	return 0;
}

