#include "stdafx.h"
#include "MyString.h"

int CompareStrings(CMyString const& string1, CMyString const& string2)
{
	size_t length = (string1.GetLength() < string2.GetLength()) ? string1.GetLength() : string2.GetLength();
	int cmp = std::memcmp(string1.GetStringData(), string2.GetStringData(), length);

	if (cmp != 0)
	{
		return cmp;
	}

	if (string1.GetLength() < string2.GetLength())
	{
		return -1;
	}
	else if (string1.GetLength() > string2.GetLength())
	{
		return 1;
	}

	return 0;
}

CMyString::CMyString()
	: m_length(0)
{
	m_chars = nullptr;
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
	: m_length(length)
{
	m_chars = new char[m_length + 1];
	std::memcpy(m_chars, pString, m_length);
	m_chars[m_length] = '\0';
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.GetStringData(), other.GetLength())
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_length(other.m_length)
{
	m_chars = other.m_chars;

	other.m_length = 0;
	other.m_chars = nullptr;
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.size())
{
}

CMyString::CMyString(size_t size)
	: m_length(size)
{
	m_chars = new char[m_length + 1];
	m_chars[m_length] = '\0';
}

CMyString::~CMyString()
{
	delete m_chars;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_chars ? m_chars : "";
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		throw std::out_of_range("index is out of range of string");
	}

	size_t lengthEnd = m_length - start;
	size_t lengthReal = (lengthEnd < length) ? lengthEnd : length;

	CMyString result(m_chars + start, lengthReal);
	return result;
}

void CMyString::Clear()
{
	m_length = 0;
	delete m_chars;
	m_chars = nullptr;
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (m_chars != other.m_chars)
	{
		CMyString copy(other);
		std::swap(m_length, copy.m_length);
		std::swap(m_chars, copy.m_chars);
	}

	return *this;
}

CMyString& CMyString::operator=(CMyString&& other)
{
	if (m_chars != other.m_chars)
	{
		m_length = other.m_length;
		m_chars = other.m_chars;

		other.m_length = 0;
		other.m_chars = nullptr;
	}

	return *this;
}

CMyString& CMyString::operator+=(CMyString const& other)
{
	CMyString result(m_length + other.m_length);
	
	std::memcpy(result.m_chars, m_chars, m_length);
	std::memcpy(result.m_chars + m_length, other.m_chars, other.m_length);
	
	std::swap(m_length, result.m_length);
	std::swap(m_chars, result.m_chars);

	return *this;
}

CMyString const operator+(CMyString const& string1, CMyString const& string2)
{
	CMyString result(string1.GetLength() + string2.GetLength());
	std::memcpy(result.m_chars, string1.m_chars, string1.m_length);
	std::memcpy(result.m_chars + string1.m_length, string2.m_chars, string2.m_length);
	return result;
}

const char& CMyString::operator[](size_t index) const
{
	if (index >= m_length)
	{
		throw std::out_of_range("index is out of range of string");
	}

	return m_chars[index];
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::out_of_range("index is out of range of string");
	}

	return m_chars[index];
}

bool const operator==(CMyString const& string1, CMyString const& string2)
{
	return CompareStrings(string1, string2) == 0;
}

bool const operator!=(CMyString const& string1, CMyString const& string2)
{
	return CompareStrings(string1, string2) != 0;
}

bool const operator<(CMyString const& string1, CMyString const& string2)
{
	return CompareStrings(string1, string2) < 0;
}

bool const operator>(CMyString const& string1, CMyString const& string2)
{
	return CompareStrings(string1, string2) > 0;
}

bool const operator<=(CMyString const& string1, CMyString const& string2)
{
	return CompareStrings(string1, string2) <= 0;
}

bool const operator>=(CMyString const& string1, CMyString const& string2)
{
	return CompareStrings(string1, string2) >= 0;
}

std::ostream& operator<<(std::ostream& strm, CMyString const& myStr)
{
	for (size_t i = 0; i < myStr.GetLength(); ++i)
	{
		strm << myStr[i];
	}

	return strm;
}

std::istream& operator>>(std::istream& strm, CMyString& myStr)
{
	std::string str;
	strm >> str;
	myStr = str;
	return strm;
}
