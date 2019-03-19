#include "stdafx.h"
#include "ExpandTemplate.h"

const int MAXN = 256;
using StateMatrix = int[MAXN][MAXN];
using ReturnString = std::string[MAXN];
struct Bor
{
	StateMatrix matrix;
	ReturnString returnString;
};

std::string Replace(const std::string& inputString, Bor& bor)
{
	std::string str;
	int state = 0;
	size_t len = inputString.size();
	for (size_t i = 0; i < len; ++i)
	{
		int k = inputString[i] - ' ';

		if (state != 0)
		{
			if (bor.matrix[k][state] == 0)
			{
				str += bor.returnString[state];
				state = 0;
			}
			else
			{
				state = bor.matrix[k][state];
			}
		}
		if (state == 0)
		{
			if (bor.matrix[k][state] == 0)
			{
				str += inputString[i];
			}
			else
			{
				state = bor.matrix[k][state];
			}
		}
	}
	if (state != 0)
	{
		str += bor.returnString[state];
	}
	return str;
}

void BuildBor(Bor& bor, std::map<std::string, std::string> const& params)
{
	for (int i = 0; i < MAXN; ++i)
		for (int j = 0; j < MAXN; ++j)
			bor.matrix[i][j] = 0;

	int state = 0;
	int nextState = 1;
	std::string strToZeroState;
	for (auto param : params)
	{
		std::string str = param.first;
		int len = (int)str.size();
		for (int i = 0; i < len; ++i)
		{
			int k = str[i] - ' ';
			if (k > MAXN)
			{
				std::cout << "k > MAXN" << std::endl;
				return;
			}
			strToZeroState += str[i];
			if (bor.matrix[k][state] == 0)
			{
				bor.matrix[k][state] = nextState;
				state = nextState;
				++nextState;
				if (nextState > MAXN)
				{
					std::cout << "nextState > MAXN" << std::endl;
					return;
				}
			}
			else
			{
				state = bor.matrix[k][state];
			}

			if (i == len - 1)
			{
				bor.returnString[state] = param.second;
			}
			else if (bor.returnString[state] == "")
			{
				bor.returnString[state] = strToZeroState;
			}
			else
			{
				strToZeroState = bor.returnString[state];
			}

		}
		strToZeroState = "";
		state = 0;
	}
}

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params)
{
	Bor bor;
	BuildBor(bor, params);
	return Replace(tpl, bor);
}