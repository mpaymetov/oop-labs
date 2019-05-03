#include "stdafx.h"
#include "MyString.h"

CMyString::CMyString()
	: m_start(std::make_shared<CMyChar>())
	, m_end(std::make_shared<CMyChar>())
	, m_length(0)
{
	m_start->next = m_end;
}

CMyString::CMyString(const char* pString)
	: m_start(std::make_shared<CMyChar>())
	, m_end(std::make_shared<CMyChar>())
{
	m_length = strlen(pString);
	auto ptr = m_start;
	for (size_t i = 0; i < m_length; ++i)
	{
		auto charElem = std::make_shared<CMyChar>();
		charElem->data = pString[i];
		ptr->next = charElem;
		ptr = charElem;
	}
	ptr->next = m_end;
}

CMyString::CMyString(const char* pString, size_t length)
	: m_start(std::make_shared<CMyChar>())
	, m_end(std::make_shared<CMyChar>())
{
	size_t strLength = strlen(pString);
	m_length = (length < strLength) ? length : strLength;

	auto ptr = m_start;
	for (size_t i = 0; i < m_length; ++i)
	{
		auto charElem = std::make_shared<CMyChar>();
		charElem->data = pString[i];
		ptr->next = charElem;
		ptr = charElem;
	}
	ptr->next = m_end;
}

CMyString::CMyString(CMyString const& other)
	: m_start(std::make_shared<CMyChar>())
	, m_end(std::make_shared<CMyChar>())
{
	m_length = other.m_length;

	auto ptr = m_start;
	auto ptrOther = other.m_start->next;
	for (size_t i = 0; i < m_length; ++i)
	{
		auto charElem = std::make_shared<CMyChar>();
		charElem->data = ptrOther->data;
		ptr->next = charElem;
		ptr = charElem;
		ptrOther = ptrOther->next;
	}
	ptr->next = m_end;
}

CMyString::CMyString(CMyString&& other)
	: m_start(other.m_start)
	, m_end(other.m_end)
	, m_length(other.m_length)
{
	other.m_start = std::make_shared<CMyChar>();
	other.m_end = std::make_shared<CMyChar>();
	other.m_start->next = other.m_end;
	other.m_length = 0;
}

CMyString::CMyString(std::string const& stlString)
	: m_start(std::make_shared<CMyChar>())
	, m_end(std::make_shared<CMyChar>())
{
	m_length = stlString.size();

	auto temp = m_start;
	for (size_t i = 0; i < m_length; ++i)
	{
		auto charElem = std::make_shared<CMyChar>();
		charElem->data = stlString[i];
		temp->next = charElem;
		temp = charElem;
	}
	temp->next = m_end;
}

CMyString::~CMyString()
{
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	char* result = new char[m_length + 1];
	auto temp = m_start->next;
	size_t i = 0;

	while (temp != nullptr)
	{
		result[i] = temp->data;
		temp = temp->next;
		++i;
	}

	return result;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		throw std::out_of_range("index is out of range of string");
	}

	size_t l_length;
	auto temp = m_start->next;

	size_t t_length = m_length - start;
	l_length = (length < t_length) ? length : t_length;

	size_t i = 0;
	while (i < start)
	{
		temp = temp->next;
		++i;
	}

	size_t j = 0;
	char* str = new char[l_length + 1];
	while (j < l_length)
	{
		str[j] = temp->data;
		temp = temp->next;
		++j;
	}
	str[l_length] = '\0';

	CMyString result(str);
	return result;
}

void CMyString::Clear()
{
	m_length = 0;
	m_start->next = m_end;
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (m_start != other.m_start)
	{
		m_length = other.m_length;

		auto ptrOther = other.m_start->next;
		auto ptr = m_start;
		for (size_t i = 0; i < m_length; ++i)
		{
			auto charElem = std::make_shared<CMyChar>();
			charElem->data = ptrOther->data;
			ptr->next = charElem;
			ptr = charElem;
			ptrOther = ptrOther->next;
		}
		ptr->next = m_end;
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other)
{
	if (m_start != other.m_start)
	{
		m_start = other.m_start;
		m_end = other.m_end;
		other.m_start = std::make_shared<CMyChar>();
		other.m_end = std::make_shared<CMyChar>();
		other.m_start->next = other.m_end;
	}
	return *this;
}

CMyString& CMyString::operator+=(CMyString const& other)
{
	size_t length = other.GetLength();
	const char* pString = other.GetStringData();

	m_length += length;
	auto temp = m_end;

	for (size_t i = 0; i < length; ++i)
	{
		temp->data = pString[i];
		auto charElem = std::make_shared<CMyChar>();
		temp->next = charElem;
		temp = charElem;
	}
	m_end = temp;

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

	auto ptr = m_start->next;
	for (size_t i = 0; i < index; ++i)
	{
		ptr = ptr->next;
	}
	return ptr->data;
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::out_of_range("index is out of range of string");
	}

	auto ptr = m_start->next;
	for (size_t i = 0; i < index; ++i)
	{
		ptr = ptr->next;
	}
	return ptr->data;
}

bool const operator==(CMyString const& string1, CMyString const& string2)
{
	size_t strLength1 = string1.GetLength();
	size_t strLength2 = string2.GetLength();
	if (strLength1 != strLength2)
	{
		return false;
	}

	for (size_t i = 0; i < strLength1; ++i)
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
	size_t strLength1 = string1.GetLength();
	size_t strLength2 = string2.GetLength();
	if (strLength1 != strLength2)
	{
		return true;
	}

	for (size_t i = 0; i < strLength1; ++i)
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
	size_t strLength1 = string1.GetLength();
	size_t strLength2 = string2.GetLength();
	size_t length = (strLength1 < strLength2) ? strLength1 : strLength2;

	for (size_t i = 0; i < length; ++i)
	{
		if (string1[i] == string2[i])
		{
			continue;
		}
		else if (string1[i] < string2[i])
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (strLength1 < strLength2)
	{
		return true;
	}

	return false;
}

bool const operator>(CMyString const& string1, CMyString const& string2)
{
	size_t strLength1 = string1.GetLength();
	size_t strLength2 = string2.GetLength();
	size_t length = (strLength1 < strLength2) ? strLength1 : strLength2;

	for (size_t i = 0; i < length; ++i)
	{
		if (string1[i] == string2[i])
		{
			continue;
		}
		else if (string1[i] > string2[i])
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (strLength1 > strLength2)
	{
		return true;
	}

	return false;
}

bool const operator<=(CMyString const& string1, CMyString const& string2)
{
	size_t strLength1 = string1.GetLength();
	size_t strLength2 = string2.GetLength();
	size_t length = (strLength1 < strLength2) ? strLength1 : strLength2;

	for (size_t i = 0; i < length; ++i)
	{
		if (string1[i] == string2[i])
		{
			continue;
		}
		else if (string1[i] < string2[i])
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (strLength1 > strLength2)
	{
		return false;
	}

	return true;
}

bool const operator>=(CMyString const& string1, CMyString const& string2)
{
	size_t strLength1 = string1.GetLength();
	size_t strLength2 = string2.GetLength();
	size_t length = (strLength1 < strLength2) ? strLength1 : strLength2;

	for (size_t i = 0; i < length; ++i)
	{
		if (string1[i] == string2[i])
		{
			continue;
		}
		else if (string1[i] > string2[i])
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (strLength1 < strLength2)
	{
		return false;
	}

	return true;
}

std::ostream& operator<<(std::ostream& strm, CMyString const& myStr)
{
	auto ptr = myStr.m_start->next;

	while (ptr->next != nullptr)
	{
		strm << ptr->data;
		ptr = ptr->next;
	}

	return strm;
}

std::istream& operator>>(std::istream& strm, CMyString& myStr)
{
	std::string str;
	strm >> str;
	myStr = CMyString(str);
	return strm;
}
