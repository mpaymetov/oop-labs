#include "stdafx.h"
#include "../dictionary/dictionary.h"
#include "sstream"

bool IsEqually(const std::string &x, const std::string &y)
{
	return x == y;
}

bool DictionariesIsEqual(Dictionary &a, Dictionary &b)
{
	std::string translationA, translationB;
	for (DictionaryMap::iterator it = a.forward.begin(); it != a.forward.end(); ++it)
	{
		if (FindInDictionary(b, it->second, translationB))
		{
			FindInDictionary(b, it->second, translationA);
			if (!IsEqually(translationA, translationB))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}

TEST_CASE("FindInDyctionary returns empty string if no translation")
{
	Dictionary dictionary;
	InsertToDictionary(dictionary, "meat", "мясо");
	std::string translate;
	CHECK(!FindInDictionary(dictionary, "cat", translate));
	CHECK(IsEqually(translate, ""));
}

TEST_CASE("FindInDyctionary returns translation if exist")
{
	Dictionary dictionary;
	InsertToDictionary(dictionary, "cat", "кот");
	std::string translate;
	CHECK(FindInDictionary(dictionary, "cat", translate));
	CHECK(IsEqually(translate, "кот "));
}

TEST_CASE("FindInDyctionary returns translation if original word in different registers")
{
	Dictionary dictionary;
	InsertToDictionary(dictionary, "cAt", "кот");
	std::string translate;
	CHECK(FindInDictionary(dictionary, "cat", translate));
	CHECK(IsEqually(translate, "кот "));
	CHECK(FindInDictionary(dictionary, "CAT", translate));
	CHECK(IsEqually(translate, "кот "));
}

TEST_CASE("Test reverse translation")
{
	Dictionary dictionary;
	InsertToDictionary(dictionary, "cat", "кот");
	std::string translate;
	CHECK(FindInDictionary(dictionary, "кот", translate));
	CHECK(IsEqually(translate, "cat "));
}

TEST_CASE("FindInDyctionary returns all translation if exist")
{
	Dictionary dictionary;
	InsertToDictionary(dictionary, "cat", "кот");
	InsertToDictionary(dictionary, "cat", "кошка");
	std::string translate;
	CHECK(FindInDictionary(dictionary, "cat", translate));
	CHECK(IsEqually(translate, "кот кошка "));
	CHECK(FindInDictionary(dictionary, "кот", translate));
	CHECK(IsEqually(translate, "cat "));
}

TEST_CASE("Test save/read functions")
{
	Dictionary dictionary;
	InsertToDictionary(dictionary, "cat", "кот");
	InsertToDictionary(dictionary, "meat", "мясо");

	std::string file;
	std::stringstream stream(file);
	SaveDictionaryToStream(stream, dictionary);
	Dictionary newDictionary;
	newDictionary = ReadDictionaryFromStream(stream);

	std::string translate;
	CHECK(FindInDictionary(newDictionary, "cat", translate));
	CHECK(IsEqually(translate, "кот "));
	CHECK(FindInDictionary(newDictionary, "meat", translate));
	CHECK(IsEqually(translate, "мясо "));
	CHECK(FindInDictionary(newDictionary, "кот", translate));
	CHECK(IsEqually(translate, "cat "));
	CHECK(FindInDictionary(newDictionary, "мясо", translate));
	CHECK(IsEqually(translate, "meat "));
	CHECK(DictionariesIsEqual(dictionary, newDictionary));
}
