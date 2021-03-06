// multmatrix.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

constexpr size_t matrixSize = 3;

using Matrix3x3 = float[3][3];

void PrintMatrix(const Matrix3x3& matrix)
{
	for (int i = 0; i < matrixSize; ++i)
	{
		for (int j = 0; j < matrixSize; ++j)
		{
			std::cout.precision(3);
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

bool ReadMatrix(std::string inputMatixFileName, Matrix3x3& matrix)
{
	std::ifstream inputFile;
	inputFile.open(inputMatixFileName);
	if (!inputFile.is_open())
	{
		return false;
	}
	std::string str;
	for (int i = 0; i < matrixSize; ++i)
	{
		for (int j = 0; j < matrixSize; ++j)
		{
			if (inputFile >> str)
			{
				try
				{
					matrix[i][j] = stof(str);
				}
				catch (const std::exception& e)
				{
					std::cout << "!Error:" << e.what() << "!\n";
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

void MultMatrix(Matrix3x3& inputMatrix1, Matrix3x3& inputMatrix2, Matrix3x3& outputMatrix)
{
	for (int i = 0; i < matrixSize; ++i)
	{
		for (int j = 0; j < matrixSize; ++j)
		{
			outputMatrix[i][j] = inputMatrix1[i][0] * inputMatrix2[0][j] + inputMatrix1[i][1] * inputMatrix2[1][j] + inputMatrix1[i][2] * inputMatrix2[2][j];
		}
	}
}

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		std::cout << "invalid argument count\n"
			<< "usage: multmatrix.exe <inputMatrixFile1> <inputMatrixFile2>\n";
		return 1;
	}

	Matrix3x3 inputMatrix1, inputMatrix2, outputMatrix;

	if (ReadMatrix(argv[1], inputMatrix1) && ReadMatrix(argv[2], inputMatrix2))
	{
		MultMatrix(inputMatrix1, inputMatrix2, outputMatrix);
		PrintMatrix(outputMatrix);
	}
	else
	{
		std::cout << "Read file error" << "\n";
		return 1;
	}

	return 0;
}
