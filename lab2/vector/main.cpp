// vector.cpp: определяет точку входа для консольного приложения.
// Разделить элементы массива на половину максимального элемента

#include "stdafx.h"
#include "vector.h"

int main()
{
	std::vector<double> number;
	ReadVector(std::cin, number);
	ProcessVector(number);
	std::sort(number.begin(), number.end()); 
	PrintVector(std::cout, number);
	return 0;
}