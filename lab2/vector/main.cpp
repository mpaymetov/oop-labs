// vector.cpp: ���������� ����� ����� ��� ����������� ����������.
// ��������� �������� ������� �� �������� ������������� ��������

#include "stdafx.h"
#include "vector.h"

int main()
{
	std::vector<float> number;
	ReadVector(std::cin, number);
	ProcessVector(number);
	sort(number.begin(), number.end());
	PrintVector(std::cout, number);
	return 0;
}