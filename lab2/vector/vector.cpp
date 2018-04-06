// vector.cpp: определяет точку входа для консольного приложения.
// Разделить элементы массива на половину максимального элемента

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>



void ReadVector(std::istream &input, std::vector<float> number)
{
	std::copy(std::istream_iterator<float>(input), std::istream_iterator<float>(), back_inserter(number));
}

void ProcessVector(std::vector<float> &number)
{
	if (!number.empty())
	{
		const float nullNumber = 0.0000000001;
		float halfMaxElement = 0.5 * (*max_element(number.begin(), number.end()));
		if (std::fabs(halfMaxElement) > nullNumber)
		{
			std::transform(number.begin(), number.end(), number.begin(), [&halfMaxElement](float number)
			{
				return number / halfMaxElement;
			});
		}
	}
}

void PrintVector(std::ostream &output, std::vector<float> &number)
{
	output << std::fixed << std::setprecision(3);
	copy(number.begin(), number.end(), std::ostream_iterator<float>(output, " "));
	output << "\n";
}

