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

bool ReadMatrix(std::string inputMatixFileName, Matrix3x3& m)
{
	std::ifstream inputFile;
	inputFile.open(inputMatixFileName);
	if (!inputFile.is_open())
	{
		return false;
	}
	for (int i = 0; i < matrixSize; ++i)
	{
		for (int j = 0; j < matrixSize; ++j)
		{
			if (!(inputFile >> m[i][j]))
			{
				return false;
			}			
		}
	}
	return true;
}

bool InvertMatrix(const Matrix3x3& inputMatrix, Matrix3x3& outputMatrix)
{
	const float determinant = inputMatrix[0][0] * inputMatrix[1][1] * inputMatrix[2][2] + inputMatrix[0][1] * inputMatrix[1][2] * inputMatrix[2][0] +
		inputMatrix[1][0] * inputMatrix[2][1] * inputMatrix[0][2] - inputMatrix[0][2] * inputMatrix[1][1] * inputMatrix[2][0] -
		inputMatrix[0][1] * inputMatrix[1][0] * inputMatrix[2][2] - inputMatrix[1][2] * inputMatrix[2][1] * inputMatrix[0][0];

	if (fabs(determinant) < 0.0000001)
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
		std::cout << "invalid argument count\n" << "usage: invert.exe <inputMatrixFile>\n";
		return 1;
	}	
	
	Matrix3x3 inputMatrix, outputMatrix;

	if (ReadMatrix(argv[1], inputMatrix))
	{
		if (InvertMatrix(inputMatrix, outputMatrix))
		{
			PrintMatrix(outputMatrix);
		}
		else
		{
			std::cout << "Invert matrix imposible" << "\n";
		}
	}
	else
	{
		std::cout << "Read file error" << "\n";
		return 1;
	}
    return 0;
}
