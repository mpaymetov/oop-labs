// labyrinth.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

constexpr int maxLabyrinthSize = 100;
using Labyrinth = int[maxLabyrinthSize][maxLabyrinthSize];

bool ReadLabyrinthFromFile(const std::string& inputFileName, Labyrinth lab, int& maxLength, int& maxHeight)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "Input file can`t open\n";
		return false;
	}

	std::string line;
	int length;
	bool foundA = false, foundB = false;

	while (std::getline(inputFile, line))
	{
		length = (line.length() < maxLabyrinthSize) ? line.length() : maxLabyrinthSize;
		if (length > maxLength)
		{
			maxLength = length;
		}
		for (int i = 0; i < length; i++)
		{
			if (line[i] == '#')
			{
				lab[maxHeight][i] = -1;
			}
			else if (line[i] == 'A')
			{
				if (!foundA)
				{
					lab[maxHeight][i] = 1;
					foundA = true;
				}
				else
				{
					std::cout << "multiple A" << std::endl;
					return false;
				}
			}
			else if (line[i] == 'B')
			{
				if (!foundB)
				{
					lab[maxHeight][i] = -2;
					foundB = true;
				}
				else
				{
					std::cout << "multiple B" << std::endl;
					return false;
				}
			}
		}
		++maxHeight;
		if (maxHeight == maxLabyrinthSize)
		{
			break;
		}
	}
	
	if (!foundA || !foundB)
	{
		std::cout << "not found A or B" << std::endl;
		return false;
	}

	return true;
}

bool WriteLabyrinthtToFile(const std::string& outputFileName, Labyrinth lab, int& maxLength, int& maxHeight)
{
	std::ofstream outputFile;
	outputFile.open(outputFileName);
	if (!outputFile.is_open())
	{
		std::cout << "Output file can`t open\n";
		return false;
	}

	for (int i = 0; i < maxHeight; i++)
	{
		for (int j = 0; j < maxLength; j++)
		{
			if (lab[i][j] == -1)
			{
				outputFile << '#';
			}
			else if (lab[i][j] == 1)
			{
				outputFile << 'A';
			}
			else if (lab[i][j] == -2)
			{
				outputFile << 'B';
			}
			else if (lab[i][j] == -3)
			{
				outputFile << '.';
			}
			else
			{
				outputFile << ' ';
			}
		}
		outputFile << std::endl;
	}

	return true;
}

void PrintWay(Labyrinth lab, int step, int x, int y, const int& maxLength, const int& maxHeight)
{
	while (step != 1)
	{
		lab[x][y] = -3;

		if (x != maxHeight)
		{
			if (lab[x + 1][y] == step - 1)
			{
				--step;
				++x;
				continue;
			}
		}

		if (y != maxLength)
		{
			if (lab[x][y + 1] == step - 1)
			{
				--step;
				++y;
				continue;
			}
		}

		if (x != 0)
		{
			if (lab[x - 1][y] == step - 1)
			{
				--step;
				--x;
				continue;
			}
		}

		if (y != 0)
		{
			if (lab[x][y - 1] == step - 1)
			{
				--step;
				--y;
				continue;
			}
		}
	}
}

void FindWay(Labyrinth lab, const int& maxLength, const int& maxHeight)
{
	bool working = true, foundB = false;
	int x, y;
	int step = 0;
	while (working && !foundB)
	{
		working = false;
		step++;
		for (int i = 0; i < maxHeight; i++)
		{
			for (int j = 0; j < maxLength; j++)
			{
				if (lab[i][j] == step)
				{
					if (j != 0)
					{
						x = i, y = j - 1;
						foundB = (lab[x][y] == -2);
						if (foundB)
						{
							PrintWay(lab, step, i, j, maxLength, maxHeight);
							break;
						}

						if (lab[x][y] == 0)
						{
							lab[x][y] = step + 1;
							working = true;
						}
					}

					if (i != maxHeight)
					{
						x = i + 1, y = j;
						foundB = (lab[x][y] == -2);
						if (foundB)
						{
							PrintWay(lab, step, i, j, maxLength, maxHeight);
							break;
						}
						if (lab[x][y] == 0)
						{
							lab[x][y] = step + 1;
							working = true;
						}
					}

					if (j != maxLength)
					{
						x = i, y = j + 1;
						foundB = (lab[x][y] == -2);
						if (foundB)
						{
							PrintWay(lab, step, i, j, maxLength, maxHeight);
							break;
						}
						if (lab[x][y] == 0)
						{
							lab[x][y] = step + 1;
							working = true;
						}
					}

					if (i != 0)
					{
						x = i - 1, y = j;
						foundB = (lab[x][y] == -2);
						if (foundB)
						{
							PrintWay(lab, step, i, j, maxLength, maxHeight);
							break;
						}
						if (lab[x][y] == 0)
						{
							lab[x][y] = step + 1;
							working = true;
						}
					}
				}
			}
			if (foundB)
			{
				break;
			}
		}
	}
}

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		std::cout << "invalid argument count\n"
			<< "usage: labyrinth.exe <input file> <output file>\n";
		return 1;
	}

	std::string inputFileName = argv[1];
	std::string outputFileName = argv[2];
	Labyrinth lab;
	int maxLength = 0, maxHeight = 0;

	for (int i = 0; i < maxLabyrinthSize; i++)
		for (int j = 0; j < maxLabyrinthSize; j++)
			lab[i][j] = 0;

	if (!ReadLabyrinthFromFile(inputFileName, lab, maxLength, maxHeight))
	{
		return 1;
	}

	FindWay(lab, maxLength, maxHeight);

	if (!WriteLabyrinthtToFile(outputFileName, lab, maxLength, maxHeight))
	{
		return 1;
	}

    return 0;
}

