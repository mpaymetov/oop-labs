#include "stdafx.h"
#include "MyString.h"

CMyString::CMyString()
	: m_start(std::make_shared<CMyChar>())
	, m_end(std::make_shared<CMyChar>())
	, m_length(0)
{
	m_start->next = m_end;
}

// конструктор, инициализирующий строку данными строки
// с завершающим нулевым символом
CMyString::CMyString(const char* pString)
	: m_start(std::make_shared<CMyChar>())
	, m_end(std::make_shared<CMyChar>())
{
	m_length = strlen(pString);

	auto temp = m_start;
	for (size_t i = 0; i < m_length; ++i)
	{
		auto charElem = std::make_shared<CMyChar>();
		charElem->data = pString[i];
		temp->next = charElem;
		temp = charElem;
	}
	temp->next = m_end;
}

// конструктор, инициализирующий строку данными из
// символьного массива заданной длины
CMyString::CMyString(const char* pString, size_t length)
	: m_start(std::make_shared<CMyChar>())
	, m_end(std::make_shared<CMyChar>())
{
	size_t strLength = strlen(pString);
	m_length = (length < strLength) ? length : strLength;

	auto temp = m_start;
	for (size_t i = 0; i < m_length; ++i)
	{
		auto charElem = std::make_shared<CMyChar>();
		charElem->data = pString[i];
		temp->next = charElem;
		temp = charElem;
	}
	temp->next = m_end;
}

// конструктор копирования
CMyString::CMyString(CMyString const& other)
	: m_start(std::make_shared<CMyChar>())
	, m_end(std::make_shared<CMyChar>())
{
	const char* pString = other.GetStringData();
	m_length = strlen(pString);

	auto temp = m_start;
	for (size_t i = 0; i < m_length; ++i)
	{
		auto charElem = std::make_shared<CMyChar>();
		charElem->data = pString[i];
		temp->next = charElem;
		temp = charElem;
	}
	temp->next = m_end;
}

// перемещающий конструктор (для компиляторов, совместимых с C++11)
//  реализуется совместно с перемещающим оператором присваивания
CMyString::CMyString(CMyString&& other)
	: m_start(other.m_start)
	, m_end(other.m_end)
	, m_length(other.m_length)
{
}

// конструктор, инициализирующий строку данными из
// строки стандартной библиотеки C++
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

// деструктор класса - освобождает память, занимаемую символами строки
CMyString::~CMyString()
{
}

// возвращает длину строки (без учета завершающего нулевого символа)
size_t CMyString::GetLength() const
{
	return m_length;
}

// возвращает указатель на массив символов строки.
// В конце массива обязательно должен быть завершающий нулевой символ
// даже если строка пустая
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

// возвращает подстроку с заданной позиции длиной не больше length символов
CMyString CMyString::SubString(size_t start, size_t length) const
{
	size_t l_length;
	auto temp = m_start->next;

	if (start < m_length)
	{
		size_t t_length = m_length - start;
		l_length = (length < t_length) ? length : t_length;

		size_t i = 0;
		while (i < start)
		{
			temp = temp->next;
			++i;
		}
	}
	else
	{
		l_length = 0;
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

// очистка строки (строка становится снова нулевой длины)
void CMyString::Clear()
{
	m_length = 0;
	m_start->next = m_end;
}

CMyString& CMyString::operator=(CMyString const& other)
{
	m_length = other.GetLength();
	const char* pString = other.GetStringData();

	auto temp = m_start;
	for (size_t i = 0; i < m_length; ++i)
	{
		auto charElem = std::make_shared<CMyChar>();
		charElem->data = pString[i];
		temp->next = charElem;
		temp = charElem;
	}
	temp->next = m_end;

	return *this;
}

CMyString& CMyString::operator=(CMyString&& other)
{
	m_start = other.m_start;
	m_end = other.m_end;
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
	std::string str1(string1.GetStringData());
	std::string str2(string2.GetStringData());
	std::string str3 = str1 + str2;
	CMyString result(str3);
	return result;
}

bool const operator==(CMyString const& string1, CMyString const& string2)
{
	return true;
}

bool const operator!=(CMyString const& string1, CMyString const& string2)
{
	return true;
}

bool const operator<(CMyString const& string1, CMyString const& string2)
{
	return true;
}

bool const operator>(CMyString const& string1, CMyString const& string2)
{
	return true;
}

bool const operator<=(CMyString const& string1, CMyString const& string2)
{
	return true;
}

bool const operator>=(CMyString const& string1, CMyString const& string2)
{
	return true;
}

std::ostream& operator<<(std::ostream& strm, CMyString const& myStr)
{
	return strm;
}

std::istream& operator>>(std::istream& strm, CMyString& myStr)
{
	return strm;
}