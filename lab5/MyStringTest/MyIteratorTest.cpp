#include "stdafx.h"
#include "../MyString/MyString.h"

TEST_CASE("test CMyIterator begin() & operator*")
{
	const char* pString = "Hello";
	CMyString str(pString);
	auto it = str.begin();
	CHECK(*it == 'H');
}

TEST_CASE("test CMyIterator operator postfix & prefix increment")
{
	const char* pString = "Hello";
	CMyString str(pString);
	auto it = str.begin();
	it++;
	CHECK(*it == 'e');
	++it;
	CHECK(*it == 'l');
}

TEST_CASE("test CMyIterator end() & operator postfix & prefix decrement")
{
	const char* pString = "Hello";
	CMyString str(pString);
	auto it = str.end();
	it--;
	CHECK(*it == 'o');
	--it;
	CHECK(*it == 'l');
}

TEST_CASE("test CMyIterator operator []")
{
	const char* pString = "Hello";
	CMyString str(pString);
	auto it = str.begin();
	CHECK(it[1] == 'e');
	CHECK(it[4] == 'o');
}

TEST_CASE("test CMyIterator operator =")
{
	const char* pString = "Hello";
	CMyString str(pString);
	auto firstIt = str.begin();
	auto secondIt = str.end();
	secondIt = firstIt;
	CHECK(*secondIt == 'H');
}

TEST_CASE("test CMyIterator operator +=")
{
	const char* pString = "Hello";
	CMyString str(pString);
	auto it = str.begin();
	it += 4;
	CHECK(*it == 'o');
}

TEST_CASE("test CMyIterator operator + offset")
{
	const char* pString = "Hello";
	CMyString str(pString);
	auto firstIt = str.begin();
	auto secondIt = str.end();
	secondIt = firstIt + 4;
	CHECK(*secondIt == 'o');
}

TEST_CASE("test CMyIterator operator -=")
{
	const char* pString = "Hello";
	CMyString str(pString);
	auto it = str.end();
	it -= 4;
	CHECK(*it == 'e');
}

TEST_CASE("test CMyIterator operator - offset")
{
	const char* pString = "Hello";
	CMyString str(pString);
	auto firstIt = str.begin();
	auto secondIt = str.end();
	firstIt = secondIt - 4;
	CHECK(*firstIt == 'e');
}

TEST_CASE("test CMyIterator operator - iterator")
{
	const char* pString = "Hello";
	CMyString str(pString);
	auto firstIt = str.begin();
	auto secondIt = str.end();
	ptrdiff_t offset = secondIt - firstIt;
	CHECK(offset == 5);
}

TEST_CASE("test CMyIterator cbegin()")
{
	const char* pString = "Hello";
	const CMyString str(pString);
	auto const it = str.cbegin();
	CHECK(*it == 'H');
}

TEST_CASE("test CMyIterator cend()")
{
	const char* pString = "Hello";
	const CMyString str(pString);
	auto const it = str.cend();
	auto second = it - 1;
	CHECK(*second == 'o');
}

TEST_CASE("test CMyIterator rbegin()")
{
	const char* pString = "Hello";
	CMyString str(pString);
	auto it = str.rbegin();
	CHECK(*it == 'o');
	it++;
	CHECK(*it == 'l');
}

TEST_CASE("test CMyIterator rend()")
{
	const char* pString = "Hello";
	CMyString str(pString);
	auto it = str.rend();
	it--;
	CHECK(*it == 'H');
	it--;
	CHECK(*it == 'e');
}

TEST_CASE("test CMyIterator crbegin()")
{
	const char* pString = "Hello";
	const CMyString str(pString);
	auto const it = str.crbegin();
	CHECK(*it == 'o');
}

TEST_CASE("test CMyIterator crend()")
{
	const char* pString = "Hello";
	const CMyString str(pString);
	auto const it = str.crend();
	auto secondIt = it - 1;
	CHECK(*secondIt == 'H');
}

TEST_CASE("test CMyIterator operator for")
{
	const char* pString = "Hello";
	CMyString str(pString);
	size_t i = 0;
	for (auto it = str.begin(); it < str.end(); ++it)
	{
		CHECK(*it == str[i]);
		++i;
	}
}

TEST_CASE("test CMyIterator operator range-based for")
{
	const char* pString = "Hello";
	CMyString str(pString);
	size_t i = 0;
	for (auto ch : str)
	{
		CHECK(ch == str[i]);
		++i;
	}
}

TEST_CASE("test CMyIterator assignment iterator to const iterator")
{
	const char* pString = "Hello";
	CMyString str(pString);
	CMyString::iterator it = str.begin();
	CMyString::const_iterator cit;
	cit = it;
	auto ch = *cit;
	CHECK(ch == 'H');
}

