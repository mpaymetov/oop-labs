#pragma once
#include "stdafx.h"

typedef std::map<std::string, std::string> HtmlEntitiesMap;

std::string HtmlDecode(const std::string &html);
