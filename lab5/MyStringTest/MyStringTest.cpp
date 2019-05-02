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
	CHECK(strcmp(second.GetStringData(), pString) == 0);
}

TEST_CASE("test CMyString SubString")
{
	const char* pString = "Hello World";
	const char* test = "World";
	CMyString first(pString);
	CMyString second = first.SubString(6, 5);
	CHECK(strcmp(second.GetStringData(), test) == 0);

	CHECK_THROWS_AS(first.SubString(15, 5), std::out_of_range);
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

TEST_CASE("test CMyString operator [] const")
{
	const char* pString = "Hello";
	CMyString first(pString);
	const char ch = first[1];
	CHECK(ch == 'e');
	CHECK_THROWS_AS(first[8], std::out_of_range);
}

TEST_CASE("test CMyString operator []")
{
	const char* pString = "Hello";
	CMyString first(pString);
	first[3] = 'i';
	CHECK(strcmp(first.GetStringData(), "Helio") == 0);
	CHECK_THROWS_AS(first[8] = 'e', std::out_of_range);
}

TEST_CASE("test CMyString operator ==")
{
	const char* str1 = "Hello";
	CMyString first(str1);
	CMyString second(str1);
	CHECK(first == second);

	const char* str3 = "World";
	CMyString third(str3);
	CHECK(!(first == third));

	const char* str4 = "Hi";
	CMyString fourth(str4);
	CHECK(!(first == fourth));
}

TEST_CASE("test CMyString operator !=")
{
	const char* str1 = "Hello";
	CMyString first(str1);
	CMyString second(str1);
	CHECK(!(first != second));

	const char* str3 = "World";
	CMyString third(str3);
	CHECK(first != third);

	const char* str4 = "Hi";
	CMyString fourth(str4);
	CHECK(first != fourth);
}

TEST_CASE("test CMyString operator <")
{
	const char* str1 = "Hello";
	CMyString first(str1);
	CMyString second(str1);
	CHECK(!(first < second));

	const char* str3 = "World";
	CMyString third(str3);
	CHECK(first < third);
	CHECK(!(third < first));

	const char* str4 = "Helio";
	CMyString fourth(str4);
	CHECK(fourth < first);
	CHECK(!(first < fourth));

	const char* str5 = "Hell";
	CMyString fifth(str5);
	CHECK(fifth < first);
	CHECK(!(first < fifth));
}

TEST_CASE("test CMyString operator >")
{
	const char* str1 = "Hello";
	CMyString first(str1);
	CMyString second(str1);
	CHECK(!(first > second));

	const char* str3 = "World";
	CMyString third(str3);
	CHECK(!(first > third));
	CHECK(third > first);

	const char* str4 = "Helio";
	CMyString fourth(str4);
	CHECK(first > fourth);
	CHECK(!(fourth > first));

	const char* str5 = "Hell";
	CMyString fifth(str5);
	CHECK(!(fifth > first));
	CHECK(first > fifth);
}

TEST_CASE("test CMyString operator <=")
{
	const char* str1 = "Hello";
	CMyString first(str1);
	CMyString second(str1);
	CHECK(first <= second);

	const char* str3 = "World";
	CMyString third(str3);
	CHECK(!(third <= first));
	CHECK(first <= third);

	const char* str4 = "Helio";
	CMyString fourth(str4);
	CHECK(fourth <= first);
	CHECK(!(first <= fourth));

	const char* str5 = "Hell";
	CMyString fifth(str5);
	CHECK(fifth <= first);
	CHECK(!(first <= fifth));
}

TEST_CASE("test CMyString operator >=")
{
	const char* str1 = "Hello";
	CMyString first(str1);
	CMyString second(str1);
	CHECK(first >= second);

	const char* str3 = "World";
	CMyString third(str3);
	CHECK(!(first >= third));
	CHECK(third >= first);

	const char* str4 = "Helio";
	CMyString fourth(str4);
	CHECK(first >= fourth);
	CHECK(!(fourth >= first));

	const char* str5 = "Hell";
	CMyString fifth(str5);
	CHECK(!(fifth >= first));
	CHECK(first >= fifth);
}

TEST_CASE("test CMyString operator <<")
{
	const char* str = "Hello";
	CMyString first(str);
	std::ostringstream strm;
	strm << first;
	CHECK(str == strm.str());
}

TEST_CASE("test CMyString operator >>")
{
	const char* str = "Hello";
	CMyString first;
	std::string strTest(str);
	std::istringstream strm(strTest);
	strm >> first;
	CHECK(strcmp(first.GetStringData(), str) == 0);
}


