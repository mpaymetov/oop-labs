#include "stdafx.h"
#include "..\ExpandTemplate\ExpandTemplate.h"

TEST_CASE("ExpandTemplate test")
{
	std::map<std::string, std::string> params;
	params["funny"] = "serious";
	std::string inputStr = "funny moments";
	CHECK(ExpandTemplate("funny moments", params) == "serious moments");
}

TEST_CASE("ExpandTemplate test2")
{
	std::map<std::string, std::string> params;
	std::string const tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
	params["%USER_NAME%"] = "Super %USER_NAME% {WEEK_DAY}";
	params["{WEEK_DAY}"] = "Friday. {WEEK_DAY}";
	std::string checkStr = ExpandTemplate(tpl, params);
	CHECK(checkStr == "Hello, Super %USER_NAME% {WEEK_DAY}. Today is Friday. {WEEK_DAY}.");
}

TEST_CASE("ExpandTemplate test3")
{
	std::map<std::string, std::string> params;
	std::string const tpl = "-AABBCCCCCABC+";
	params["A"] = "[a]";
	params["AA"] = "[aa]";
	params["B"] = "[b]";
	params["BB"] = "[bb]";
	params["C"] = "[c]";
	params["CC"] = "[cc]";
	std::string checkStr = ExpandTemplate(tpl, params);
	CHECK(checkStr == "-[aa][bb][cc][cc][c][a][b][c]+");
}

TEST_CASE("ExpandTemplate test4")
{
	std::map<std::string, std::string> params;
	params["moments"] = "games";
	std::string inputStr = "funny moments";
	CHECK(ExpandTemplate("funny moments", params) == "funny games");
}

TEST_CASE("ExpandTemplate test empty key string")
{
	std::map<std::string, std::string> params;
	params[""] = "*";
	params["funny"] = "serious";
	std::string inputStr = "funny moments";
	CHECK(ExpandTemplate("funny moments", params) == "serious moments");
}
