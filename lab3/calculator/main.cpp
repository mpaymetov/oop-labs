#include "stdafx.h"
#include "UserInterface.h"
#include "Calculator.h"

int main()
{
	CCalculator calculator;
	CUserInterface userInterface(calculator, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!userInterface.ExecuteCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
	return 0;
}

