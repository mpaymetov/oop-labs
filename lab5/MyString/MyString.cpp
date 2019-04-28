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
{
}

// конструктор копирования
CMyString::CMyString(CMyString const& other)
{
}

// перемещающий конструктор (для компиляторов, совместимых с C++11)
//  реализуется совместно с перемещающим оператором присваивания
CMyString::CMyString(CMyString&& other)
{
}

// конструктор, инициализирующий строку данными из
// строки стандартной библиотеки C++
CMyString::CMyString(std::string const& stlString)
{
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
	char* result = new char[m_length +1];
	auto temp = m_start->next;
	size_t i = 0;
	
	while (temp->next != nullptr)
	{
		result[i] = temp->data;
		temp = temp->next;
		++i;
	}
	result[i] = '\0';

	return result;
}

// возвращает подстроку с заданной позиции длиной не больше length символов
CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start + length > m_length)
	{
		std::cout << "error" << std::endl;
	}

	CMyString result;
	return result;
}

// очистка строки (строка становится снова нулевой длины)
void CMyString::Clear()
{
}