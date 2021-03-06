// labyrinth.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

constexpr int maxLabyrinthSize = 100;
using Map = int[maxLabyrinthSize][maxLabyrinthSize];
struct Labyrinth
{
	Map map;
	int maxLength;
	int maxHeight;
}; 
const char borderLabyrinthChar = '#';
const char startPositionChar = 'A';
const char finishPositionChar = 'B';
const char wayChar = '.';
const char emptyPlaceChar = ' ';
const int borderLabyrinthNum = -1;
const int startPositionNum = 1;
const int finishPositionNum = -2;
const int wayNum = -3;
const int emptyPlaceNum = 0;

int CharToCellIndex(char ch)
{
	switch (ch)
	{
		case borderLabyrinthChar: return borderLabyrinthNum;
		case startPositionChar: return startPositionNum;
		case finishPositionChar: return finishPositionNum;
		default: return emptyPlaceNum;
	}
}

bool ReadLabyrinthFromFile(const std::string& inputFileName, Labyrinth& lab)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "Input file can`t open\n";
		return false;
	}

	for (int i = 0; i < maxLabyrinthSize; i++)
		for (int j = 0; j < maxLabyrinthSize; j++)
			lab.map[i][j] = 0;
	lab.maxHeight = 0;
	lab.maxLength = 0;

	std::string line;
	int strLength;
	bool startPointWasFound = false, endPointWasFound = false;

	while (std::getline(inputFile, line))
	{
		int length = static_cast<int>(line.length());
		strLength = (length < maxLabyrinthSize) ? length : maxLabyrinthSize;
		if (strLength > lab.maxLength)
		{
			lab.maxLength = strLength;
		}
		
		for (int i = 0; i < strLength; i++)
		{
			lab.map[lab.maxHeight][i] = CharToCellIndex(line[i]);
			if (line[i] == startPositionChar)
			{
				if (!startPointWasFound)
				{
					startPointWasFound = true;
				}
				else
				{
					std::cout << "multiple A" << std::endl;
					return false;
				}
			}
			else if (line[i] == finishPositionChar)
			{
				if (!endPointWasFound)
				{
					endPointWasFound = true;
				}
				else
				{
					std::cout << "multiple B" << std::endl;
					return false;
				}
			}
		}
		
		++lab.maxHeight;
		if (lab.maxHeight == maxLabyrinthSize)
		{
			break;
		}
	}
	
	if (!startPointWasFound)
	{
		std::cout << "not found A" << std::endl;
		return false;
	}
	
	if (!endPointWasFound)
	{
		std::cout << "not found B" << std::endl;
		return false;
	}

	return true;
}

char CellIndexToChar(int num)
{
	switch (num)
	{
		case borderLabyrinthNum: return borderLabyrinthChar;
		case startPositionNum: return startPositionChar;
		case finishPositionNum: return finishPositionChar;
		case wayNum: return wayChar;
		default: return emptyPlaceChar;
	}
}

bool WriteLabyrinthtToFile(const std::string& outputFileName, Labyrinth& lab)
{
	std::ofstream outputFile;
	outputFile.open(outputFileName);
	if (!outputFile.is_open())
	{
		std::cout << "Output file can`t open\n";
		return false;
	}

	for (int i = 0; i < lab.maxHeight; i++)
	{
		for (int j = 0; j < lab.maxLength; j++)
		{
			outputFile << CellIndexToChar(lab.map[i][j]);
		}
		outputFile << std::endl;
	}

	return true;
}

bool TryForwardStepBy(Labyrinth& lab, int step, int x, int y, int dx, int dy)
{
	int lx = x + dx;
	int ly = y + dy;
	if ((lx >= 0) && (lx < lab.maxHeight) && (ly >= 0) && (ly < lab.maxLength))
	{
		if (lab.map[lx][ly] == emptyPlaceNum)
		{
			lab.map[lx][ly] = step + 1;
			return true;
		}
	}
	return false;
}

bool TryForwardStep(Labyrinth& lab, int step, int i, int j)
{
	bool moveUp = TryForwardStepBy(lab, step, i, j, -1, 0);
	bool moveLeft = TryForwardStepBy(lab, step, i, j, 0, -1);
	bool moveDown = TryForwardStepBy(lab, step, i, j, 1, 0);
	bool moveRight = TryForwardStepBy(lab, step, i, j, 0, 1);
	bool tryForwardStep = moveUp || moveLeft || moveDown || moveRight;
	return tryForwardStep;
}

bool CheckFinishPlaceBy(Labyrinth& lab, int x, int y, int dx, int dy)
{
	int lx = x + dx;
	int ly = y + dy;
	if ((lx >= 0) && (lx < lab.maxLength) && (ly >= 0) && (ly < lab.maxHeight))
	{
		return (lab.map[lx][ly] == finishPositionNum);
	}
	return false;
}

bool CheckFinishPlace(Labyrinth& lab, int x, int y)
{
	return CheckFinishPlaceBy(lab, x, y, -1, 0) || CheckFinishPlaceBy(lab, x, y, 0, -1) || CheckFinishPlaceBy(lab, x, y, 1, 0) || CheckFinishPlaceBy(lab, x, y, 0, 1);
}

bool TryBackwardStepBy(Labyrinth& lab, int& step, int& x, int& y, int dx, int dy)
{
	int lx = x + dx;
	int ly = y + dy;
	if ((lx >= 0) && (lx < lab.maxHeight) && (ly >= 0) && (ly < lab.maxLength))
	{
		if (lab.map[lx][ly] == step - 1)
		{
			--step;
			x = lx;
			y = ly;
			return true;
		}
	}
	return false;
}

void RunWaveAlgorithm(Labyrinth& lab)
{
	bool working = true, endPointWasFound = false, workingTemp = false;
	int x, y;
	int step = 0;
	while (working && !endPointWasFound)
	{
		working = false;
		step++;
		int i = 0;
		while ((i < lab.maxHeight) && !endPointWasFound)
		{
			int j = 0;
			while ((j < lab.maxLength) && !endPointWasFound)
			{
				if (lab.map[i][j] == step)
				{
					endPointWasFound = CheckFinishPlace(lab, i, j);
					workingTemp = TryForwardStep(lab, step, i, j);
					working = working || workingTemp;
				}
				if (endPointWasFound)
				{
					x = i;
					y = j;
				}
				j++;
			}
			i++;
		}
	}
	
	if (endPointWasFound)
	{
		while (step != 1)
		{
			lab.map[x][y] = wayNum;
			if (!TryBackwardStepBy(lab, step, x, y, 0, 1))
			{
				if (!TryBackwardStepBy(lab, step, x, y, 1, 0))
				{
					if (!TryBackwardStepBy(lab, step, x, y, 0, -1))
					{
						TryBackwardStepBy(lab, step, x, y, -1, 0);
					}
				}
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

	if (!ReadLabyrinthFromFile(inputFileName, lab))
	{
		return 1;
	}

	RunWaveAlgorithm(lab);

	if (!WriteLabyrinthtToFile(outputFileName, lab))
	{
		return 1;
	}

    return 0;
}
