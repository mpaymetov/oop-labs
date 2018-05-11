#include "stdafx.h"
#include "../dictionary/dictionary.h"

bool IsEqually(const std::string &x, const std::string &y)
{
	return x == y;
}

TEST_CASE("FindInDyctionary returns empty string if no translation")
{
	DictionaryType dictionary, reverseDyctionary;
	InsertToDyctionary(dictionary, reverseDyctionary, "meat", "мясо");
	std::string translate;
	bool isFind = FindInDyctionary(dictionary, reverseDyctionary, "cat", translate);
	CHECK(!isFind);
	CHECK(IsEqually(translate, ""));
}

TEST_CASE("FindInDyctionary returns translation if exist")
{
	DictionaryType dictionary, reverseDyctionary;
	InsertToDyctionary(dictionary, reverseDyctionary, "cat", "кот");
	std::string translate;
	bool isFind = FindInDyctionary(dictionary, reverseDyctionary, "cat", translate);
	CHECK(isFind);
	CHECK(IsEqually(translate, "кот "));
}

TEST_CASE("FindInDyctionary returns all translation if exist")
{
	DictionaryType dictionary, reverseDyctionary;
	InsertToDyctionary(dictionary, reverseDyctionary, "cat", "кот");
	InsertToDyctionary(dictionary, reverseDyctionary, "cat", "кошка");
	std::string translate;
	bool isFind = FindInDyctionary(dictionary, reverseDyctionary, "cat", translate);
	CHECK(isFind);
	CHECK(IsEqually(translate, "кот кошка "));
	isFind = FindInDyctionary(dictionary, reverseDyctionary, "кот", translate);
	CHECK(isFind);
	CHECK(IsEqually(translate, "cat "));
}
