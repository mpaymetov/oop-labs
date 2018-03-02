// invert.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

constexpr size_t matrixSize = 3;

using Matrix3x3 = float[3][3];

void PrintMatrix(const Matrix3x3& m)
{
	for (int i = 0; i < matrixSize; ++i)
	{
		for (int j = 0; j < matrixSize; ++j)
		{
			std::cout.precision(3);
			std::cout << m[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void ReadMatrix(std::istream& inputMatixFile, Matrix3x3& m)
{
	for (int i = 0; i < matrixSize; ++i)
	{
		for (int j = 0; j < matrixSize; ++j)
		{
			inputMatixFile >> m[i][j];
		}
		std::cout << "\n";
	}
}

bool invertMatrix(Matrix3x3& inputMatrix, Matrix3x3& outputMatrix)
{
	const float determinant = inputMatrix[0][0] * inputMatrix[1][1] * inputMatrix[2][2] + inputMatrix[0][1] * inputMatrix[1][2] * inputMatrix[2][0] +
		inputMatrix[1][0] * inputMatrix[2][1] * inputMatrix[0][2] - inputMatrix[0][2] * inputMatrix[1][1] * inputMatrix[2][0] -
		inputMatrix[0][1] * inputMatrix[1][0] * inputMatrix[2][2] - inputMatrix[1][2] * inputMatrix[2][1] * inputMatrix[0][0];

	if (determinant == 0)
	{
		return false;
	}
	else
	{
		outputMatrix[0][0] = (inputMatrix[1][1] * inputMatrix[2][2] - inputMatrix[1][2] * inputMatrix[2][1]) / determinant;
		outputMatrix[1][0] = -1 * (inputMatrix[1][0] * inputMatrix[2][2] - inputMatrix[1][2] * inputMatrix[2][0]) / determinant;
		outputMatrix[2][0] = (inputMatrix[1][0] * inputMatrix[2][1] - inputMatrix[1][1] * inputMatrix[2][0]) / determinant;

		outputMatrix[0][1] = -1 * (inputMatrix[0][1] * inputMatrix[2][2] - inputMatrix[0][2] * inputMatrix[2][1]) / determinant;
		outputMatrix[1][1] = (inputMatrix[0][0] * inputMatrix[2][2] - inputMatrix[2][0] * inputMatrix[0][2]) / determinant;
		outputMatrix[2][1] = -1 * (inputMatrix[0][0] * inputMatrix[2][1] - inputMatrix[0][1] * inputMatrix[2][0]) / determinant;

		outputMatrix[0][2] = (inputMatrix[0][1] * inputMatrix[1][2] - inputMatrix[0][2] * inputMatrix[1][1]) / determinant;
		outputMatrix[1][2] = -1 * (inputMatrix[0][0] * inputMatrix[1][2] - inputMatrix[0][2] * inputMatrix[1][0]) / determinant;
		outputMatrix[2][2] = (inputMatrix[0][0] * inputMatrix[1][1] - inputMatrix[0][1] * inputMatrix[1][0]) / determinant;
	}
	return true;
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		std::cout << "invalid argument count\n"
			<< "usage: invert.exe <inputMatrixFile>\n";
		return 1;
	}

	std::ifstream inputFile;
	inputFile.open(argv[1]);
	
	Matrix3x3 inputMatrix, outputMatrix;
	ReadMatrix(inputFile, inputMatrix);

	if (invertMatrix(inputMatrix, outputMatrix))
	{
		PrintMatrix(outputMatrix);
	}
	else
	{
		std::cout << "Invert matrix imposible" << "\n";
	}

    return 0;
}