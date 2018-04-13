// vector.cpp: определяет точку входа для консольного приложения.
// Разделить элементы массива на половину максимального элемента

#include "stdafx.h"

void ReadVector(std::istream &input, std::vector<double> &number)
{
	std::copy(std::istream_iterator<double>(input), std::istream_iterator<double>(), back_inserter(number));
}

void ProcessVector(std::vector<double> &number)
{
	if (!number.empty())
	{
		const double nullNumber = 0.0000000001;
		double halfMaxElement = 0.5 * (*max_element(number.begin(), number.end()));
		if (std::fabs(halfMaxElement) > nullNumber)
		{
			std::transform(number.begin(), number.end(), number.begin(), [&halfMaxElement](double number)
			{
				return number / halfMaxElement;
			});
		}
	}
}

void PrintVector(std::ostream &output, const std::vector<double> &number)
{
	output << std::fixed << std::setprecision(3);
	copy(number.begin(), number.end(), std::ostream_iterator<double>(output, " "));
	output << "\n";
}

