#include "stdafx.h"
#include "../MyString/MyString.h"

TEST_CASE("test CMyString create empty")
{
	CMyString str;
	CHECK(strcmp(str.GetStringData(), "") == 0);
}

TEST_CASE("test CMyString create from const char*")
{
	const char* pString = "Hello";
	CMyString str(pString);
	CHECK(strcmp(str.GetStringData(), pString) == 0);
}

TEST_CASE("test CMyString Get Length")
{
	const char* pString = "Hello";
	CMyString str(pString);
	CHECK(str.GetLength() == 5);
}

