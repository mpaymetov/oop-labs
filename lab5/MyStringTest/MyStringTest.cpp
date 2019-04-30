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

TEST_CASE("test CMyString create from const char* with length")
{
	const char* pString = "Hello World!";
	const char* testString = "Hello";
	CMyString str(pString, 5);
	CHECK(strcmp(str.GetStringData(), testString) == 0);
}

TEST_CASE("test CMyString create with copy constructor")
{
	const char* pString = "Hello";
	CMyString first(pString);
	CMyString second(first);
	CHECK(strcmp(second.GetStringData(), pString) == 0);
}

TEST_CASE("test CMyString create with stl string")
{
	const std::string input = "Hello";
	const char* test = "Hello";
	CMyString str(input);
	CHECK(strcmp(str.GetStringData(), test) == 0);
}

TEST_CASE("test CMyString Get Length")
{
	const char* pString = "Hello";
	CMyString str(pString);
	CHECK(str.GetLength() == 5);
}

TEST_CASE("test CMyString Clear")
{
	const char* pString = "Hello";
	CMyString str(pString);
	CHECK(strcmp(str.GetStringData(), pString) == 0);
	str.Clear();
	CHECK(strcmp(str.GetStringData(), "") == 0);
}

TEST_CASE("test CMyString operator=")
{
	const char* pString = "Hello";
	CMyString first(pString);
	CMyString second;
	second = first;
	CHECK(strcmp(second.GetStringData(), pString) == 0);
}

TEST_CASE("test CMyString create with move constructor")
{
	const char* pString = "Hello";
	CMyString first(pString);
	CMyString second = first.SubString(0);
	const char* test = second.GetStringData();
	CHECK(strcmp(second.GetStringData(), pString) == 0);
}

TEST_CASE("test CMyString SubString")
{
	const char* pString = "Hello World";
	const char* test = "World";
	CMyString first(pString);
	CMyString second = first.SubString(6, 5);
	CHECK(strcmp(second.GetStringData(), test) == 0);

	//CMyString third = first.SubString(15, 5);
	//CHECK(strcmp(third.GetStringData(), "") == 0);
}

TEST_CASE("test CMyString operator+=")
{
	const char* pString1 = "Hello ";
	const char* pString2 = "World";
	const char* test = "Hello World";

	CMyString first(pString1);
	CMyString second(pString2);
	first += second;
	CHECK(strcmp(first.GetStringData(), test) == 0);
}

TEST_CASE("test CMyString operator+ for two CMyString")
{
	const char* pString1 = "Hello ";
	const char* pString2 = "World";
	const char* test = "Hello World";

	CMyString first(pString1);
	CMyString second(pString2);
	CMyString third = first + second;
	CHECK(strcmp(third.GetStringData(), test) == 0);
}

TEST_CASE("test CMyString operator+ for std::string & CMyString")
{
	std::string first = "Hello ";
	const char* pString2 = "World";
	CMyString second(pString2);
	const char* test = "Hello World";

	CMyString third = first + second;
	CHECK(strcmp(third.GetStringData(), test) == 0);
}

TEST_CASE("test CMyString operator+ for const char* & CMyString")
{
	const char* first = "Hello ";
	const char* pString2 = "World";
	CMyString second(pString2);
	const char* test = "Hello World";

	CMyString third = first + second;
	CHECK(strcmp(third.GetStringData(), test) == 0);
}

TEST_CASE("test CMyString moving assignment operator")
{
	const char* pString = "Hello";
	CMyString first(pString);
	CMyString second(pString);
	second.Clear();
	CHECK(strcmp(second.GetStringData(), "") == 0);

	second = first.SubString(0);
	CHECK(strcmp(second.GetStringData(), pString) == 0);
}