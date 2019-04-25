#include "stdafx.h"
#include "calcControl.h"
#include "Calculator.h"

int main()
{
	CCalculator calculator;
	CCalcControl calcControl(calculator, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!calcControl.ExecuteCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
	return 0;
}

