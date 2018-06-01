#include "stdafx.h"
#include "car.h"
#include "carControl.h"

int main()
{
	CCar car; 
	CCarControl carControl(car, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!carControl.ExecuteCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
	return 0;
}

