#include "stdafx.h"
#include "MyString.h"

CMyString::CMyString()
	: m_length(0)
{
	m_chars = new char[1];
	m_chars[m_length] = '\0';
}

CMyString::CMyString(const char* pString)
{
	m_length = strlen(pString);
	m_chars = new char[m_length + 1];
	for (size_t i = 0; i < m_length; ++i)
	{
		m_chars[i] = pString[i];
	}
	m_chars[m_length] = '\0';
}

CMyString::CMyString(const char* pString, size_t length)
	: m_length(length)
{
	m_chars = new char[m_length + 1];
	for (size_t i = 0; i < m_length; ++i)
	{
		m_chars[i] = pString[i];
	}
	m_chars[m_length] = '\0';
}

CMyString::CMyString(CMyString const& other)
	: m_length(other.m_length)
{
	m_chars = new char[m_length + 1];
	for (size_t i = 0; i < m_length; ++i)
	{
		m_chars[i] = other.m_chars[i];
	}
	m_chars[m_length] = '\0';
}

CMyString::CMyString(CMyString&& other)
	: m_length(other.m_length)
{
	m_chars = other.m_chars;

	other.m_length = 0;
	other.m_chars = new char[other.m_length + 1];
	other.m_chars[other.m_length] = '\0';
}

CMyString::CMyString(std::string const& stlString)
	: m_length(stlString.size())
{
	m_chars = new char[m_length + 1];
	for (size_t i = 0; i < m_length; ++i)
	{
		m_chars[i] = stlString[i];
	}
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
	return m_chars;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		throw std::out_of_range("index is out of range of string");
	}

	size_t lengthEnd = m_length - start;
	size_t lengthReal = (lengthEnd < length) ? lengthEnd : length;

	char* str = new char[lengthReal + 1];
	for (size_t i = 0; i < lengthReal; ++i)
	{
		str[i] = m_chars[i + start];
	}
	str[lengthReal] = '\0';

	CMyString result(str);
	return result;
}

void CMyString::Clear()
{
	m_length = 0;
	m_chars = (char*)realloc(m_chars, 1);
	m_chars[m_length] = '\0';
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (m_chars != other.m_chars)
	{
		if (void* mem = std::realloc(m_chars, other.m_length + 1))
			m_chars = static_cast<char*>(mem);
		else
			throw std::bad_alloc();

		m_length = other.m_length;
		std::memcpy(m_chars, other.m_chars, other.m_length);
		m_chars[m_length] = '\0';
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
		other.m_chars = new char[other.m_length + 1];
		other.m_chars[other.m_length] = '\0';
	}

	return *this;
}

CMyString& CMyString::operator+=(CMyString const& other)
{
	if (void* mem = std::realloc(m_chars, m_length + other.m_length + 1))
		m_chars = static_cast<char*>(mem);
	else
		throw std::bad_alloc();

	std::memcpy(m_chars + m_length, other.m_chars, other.m_length);
	m_length = m_length + other.m_length;
	m_chars[m_length] = '\0';

	return *this;
}

CMyString const operator+(CMyString const& string1, CMyString const& string2)
{
	CMyString result(string1);
	result += string2;
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
	if (string1.GetLength() != string2.GetLength())
	{
		return false;
	}

	for (size_t i = 0; i < string1.GetLength(); ++i)
	{
		if (string1[i] != string2[i])
		{
			return false;
		}
	}

	return true;
}

bool const operator!=(CMyString const& string1, CMyString const& string2)
{
	if (string1.GetLength() != string2.GetLength())
	{
		return true;
	}

	for (size_t i = 0; i < string1.GetLength(); ++i)
	{
		if (string1[i] != string2[i])
		{
			return true;
		}
	}

	return false;
}

bool const operator<(CMyString const& string1, CMyString const& string2)
{
	size_t length = (string1.GetLength() < string2.GetLength()) ? string1.GetLength() : string2.GetLength();
	for (size_t i = 0; i < length; ++i)
	{
		if (string1[i] < string2[i])
		{
			return true;
		}
		else if (string1[i] > string2[i])
		{
			return false;
		}
	}

	if (string1.GetLength() < string2.GetLength())
	{
		return true;
	}

	return false;
}

bool const operator>(CMyString const& string1, CMyString const& string2)
{
	size_t length = (string1.GetLength() < string2.GetLength()) ? string1.GetLength() : string2.GetLength();
	for (size_t i = 0; i < length; ++i)
	{
		if (string1[i] > string2[i])
		{
			return true;
		}
		else if (string1[i] < string2[i])
		{
			return false;
		}
	}

	if (string1.GetLength() > string2.GetLength())
	{
		return true;
	}

	return false;
}

bool const operator<=(CMyString const& string1, CMyString const& string2)
{
	size_t length = (string1.GetLength() < string2.GetLength()) ? string1.GetLength() : string2.GetLength();
	for (size_t i = 0; i < length; ++i)
	{
		if (string1[i] < string2[i])
		{
			return true;
		}
		else if (string1[i] > string2[i])
		{
			return false;
		}
	}

	if (string1.GetLength() <= string2.GetLength())
	{
		return true;
	}

	return false;
}

bool const operator>=(CMyString const& string1, CMyString const& string2)
{
	size_t length = (string1.GetLength() < string2.GetLength()) ? string1.GetLength() : string2.GetLength();
	for (size_t i = 0; i < length; ++i)
	{
		if (string1[i] > string2[i])
		{
			return true;
		}
		else if (string1[i] < string2[i])
		{
			return false;
		}
	}

	if (string1.GetLength() >= string2.GetLength())
	{
		return true;
	}

	return false;
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

