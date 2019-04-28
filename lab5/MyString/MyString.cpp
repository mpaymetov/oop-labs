#include "stdafx.h"
#include "MyString.h"

CMyString::CMyString()
	: m_start(std::make_shared<CMyChar>())
	, m_end(std::make_shared<CMyChar>())
	, m_length(0)
{
	m_start->next = m_end;
}

// �����������, ���������������� ������ ������� ������
// � ����������� ������� ��������
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

// �����������, ���������������� ������ ������� ��
// ����������� ������� �������� �����
CMyString::CMyString(const char* pString, size_t length)
{
}

// ����������� �����������
CMyString::CMyString(CMyString const& other)
{
}

// ������������ ����������� (��� ������������, ����������� � C++11)
//  ����������� ��������� � ������������ ���������� ������������
CMyString::CMyString(CMyString&& other)
{
}

// �����������, ���������������� ������ ������� ��
// ������ ����������� ���������� C++
CMyString::CMyString(std::string const& stlString)
{
}

// ���������� ������ - ����������� ������, ���������� ��������� ������
CMyString::~CMyString()
{
}

// ���������� ����� ������ (��� ����� ������������ �������� �������)
size_t CMyString::GetLength() const
{
	return m_length;
}

// ���������� ��������� �� ������ �������� ������.
// � ����� ������� ����������� ������ ���� ����������� ������� ������
// ���� ���� ������ ������
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

// ���������� ��������� � �������� ������� ������ �� ������ length ��������
CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start + length > m_length)
	{
		std::cout << "error" << std::endl;
	}

	CMyString result;
	return result;
}

// ������� ������ (������ ���������� ����� ������� �����)
void CMyString::Clear()
{
}