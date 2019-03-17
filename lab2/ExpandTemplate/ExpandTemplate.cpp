#include "stdafx.h"
#include "ExpandTemplate.h"

const int MAXN = 256;
using StateMatrix = int[MAXN][MAXN];
using ReturnString = std::string[MAXN];

std::string Replace(const std::string& inputString, StateMatrix& bor, ReturnString& returnString)
{
	std::string str;
	int state = 0;
	size_t len = inputString.size();
	for (size_t i = 0; i < len; ++i)
	{
		int k = inputString[i] - 'A';

		if (state != 0)
		{
			if (bor[k][state] == 0)
			{
				str += returnString[state];
				state = 0;
			}
			else
			{
				state = bor[k][state];
			}
		}
		if (state == 0)
		{
			if (bor[k][state] == 0)
			{
				str += inputString[i];
			}
			else
			{
				state = bor[k][state];
			}
		}
	}
	return str;
}

void BuildBor(StateMatrix& bor, ReturnString& returnString, std::map<std::string, std::string> const& params)
{
	for (int i = 0; i < MAXN; ++i)
		for (int j = 0; j < MAXN; ++j)
			bor[i][j] = 0;

	int state = 0;
	int nextState = 1;
	std::string strToZeroState;
	for (auto param : params)
	{
		std::string str = param.first;
		int len = (int)str.size();
		for (int i = 0; i < len; ++i)
		{
			int k = str[i] - 'A';
			strToZeroState += str[i];
			if (bor[k][state] == 0)
			{
				bor[k][state] = nextState;
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
				state = bor[k][state];
			}

			if (i == len - 1)
			{
				returnString[state] = param.second;
			}
			else if (returnString[state] == "")
			{
				returnString[state] = strToZeroState;
			}
			else
			{
				strToZeroState = returnString[state];
			}

		}
		strToZeroState = "";
		state = 0;
	}
}

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params)
{
	StateMatrix bor;
	ReturnString returnString;
	BuildBor(bor, returnString, params);
	return Replace(tpl, bor, returnString);
}