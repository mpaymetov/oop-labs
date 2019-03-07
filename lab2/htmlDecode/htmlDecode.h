#pragma once
#include "stdafx.h"

typedef std::map<std::string, std::string> HtmlEntitiesMap;

struct PairSearchReplace
{
	std::string search;
	std::string replace;
};

std::string HtmlDecode(const std::string &html);
