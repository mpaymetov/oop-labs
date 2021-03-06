#include "stdafx.h"
#include "ExpandTemplate.h"

const size_t MAXN = 256;
using StateMatrix = size_t[MAXN][MAXN];
using ReturnString = std::string[MAXN];
struct Bor
{
	StateMatrix matrix;
	ReturnString returnString;
};

std::string Replace(const std::string& inputString, Bor& bor)
{
	std::string str;
	size_t state = 0;
	size_t len = inputString.size();
	for (size_t i = 0; i < len; ++i)
	{
		size_t k = inputString[i] - ' ';

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

void StringToBor(Bor& bor, const std::pair<std::string, std::string>& param, size_t& nextState)
{
	size_t state = 0;
	std::string strToZeroState;
	std::string str = param.first;
	size_t len = str.size();
	for (size_t i = 0; i < len; ++i)
	{
		size_t k = str[i] - ' ';
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
}

void BuildBor(Bor& bor, std::map<std::string, std::string> const& params)
{
	for (size_t i = 0; i < MAXN; ++i)
		for (size_t j = 0; j < MAXN; ++j)
			bor.matrix[i][j] = 0;

	size_t nextState = 1;
	for (auto&& param : params)
	{
		StringToBor(bor, param, nextState);
	}
}

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params)
{
	Bor bor;
	BuildBor(bor, params);
	return Replace(tpl, bor);
}