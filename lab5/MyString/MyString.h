#pragma once
#include "stdafx.h"

class CMyChar
{
public:
	char data = '\0';
	std::shared_ptr<CMyChar> next = nullptr;
};

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other);
	CMyString(std::string const& stlString);

	~CMyString();

	CMyString& operator=(CMyString const& other);
	CMyString& operator=(CMyString&& other);
	CMyString& operator+=(CMyString const& other);
	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	size_t GetLength() const;
	const char* GetStringData() const;

	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	void Clear();

	friend std::ostream& operator<<(std::ostream& strm, CMyString const& myStr);
	friend std::istream& operator>>(std::istream& strm, CMyString& myStr);

private:
	std::shared_ptr<CMyChar> m_start;
	std::shared_ptr<CMyChar> m_end;

	size_t m_length;
};

CMyString const operator+(CMyString const& string1, CMyString const& string2);

bool const operator==(CMyString const& string1, CMyString const& string2);
bool const operator!=(CMyString const& string1, CMyString const& string2);
bool const operator<(CMyString const& string1, CMyString const& string2);
bool const operator>(CMyString const& string1, CMyString const& string2);
bool const operator<=(CMyString const& string1, CMyString const& string2);
bool const operator>=(CMyString const& string1, CMyString const& string2);

