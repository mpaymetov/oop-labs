#include "stdafx.h"

#include <iostream>
#include <optional>
#include <string>
#include <vector>

// ��������� "�������� ����� ������", ������������ ��������
// ������������ ��������:
//  WriteChar - ������� � ����� ������
//  � ������ ������ ������� ���������� std::runtime_error
class IOutputStream
{
public:
	virtual ~IOutputStream() = default;
	virtual void WriteChar(char ch) = 0;
	// �������� ����������� ���
};

// ��������� "������� ����� ������", ������������ ��������
// ������������ ��������:
//  Read - ��������� ������ �� ������ ������
//   ���� ����� ����������, ���������� "������" ������
//   � ������ ������ ������� ���������� std::runtime_error
class IInputStream
{
public:
	virtual ~IInputStream() = default;
	virtual std::optional<char> Read() = 0;
	// �������� ����������� ���
};

// �����, ����������� ��������� IOuputStream
// � �������� ��������� ������ ���������� vector<char>, ������ �� ������� ��������� ��� �������
// �������� - �����
// ������������� ������������� ��������:
//   Clear(), ��������� ������ � �������������� � ������
//   Reset(), ������������ ������� ������ � ������ �������, �� ����� ��� ����������
class MemoryOutputStream : public IOutputStream // �������� ����������� ���
{
	// �������� ����������� ���
public:
	MemoryOutputStream(std::vector<char>* stream)
		: m_stream(stream)
	{
	}

	void WriteChar(char ch) override
	{
		if (m_it == (*m_stream).end())
		{
			try
			{
				(*m_stream).push_back(ch);
			}
			catch (std::exception&)
			{
				throw std::runtime_error("cant push_back element");
			}
			m_it = (*m_stream).end();
		}
		else
		{
			*m_it = ch;
			++m_it;
		}
	};

	void Clear()
	{
		(*m_stream).clear();
		m_it = (*m_stream).end();
	};

	void Reset()
	{
		m_it = (*m_stream).begin();
	};

private:
	std::vector<char>* m_stream;
	std::vector<char>::iterator m_it = (*m_stream).end();
};

// �����, ����������� ��������� IInputStream
// � �������� ��������� ������ ���������� vector<char>, ������ �� ������� ��������� ��� �������
// ������������� ������������� �������� Reset(), ����������� ��������� � ������ �������
class MemoryInputStream : public IInputStream // �������� ����������� ���
{
	// �������� ����������� ���
public:
	MemoryInputStream(std::vector<char>* stream)
		: m_stream(stream)
	{
	}

	std::optional<char> Read() override
	{
		std::optional<char> ch = std::nullopt;
		if (m_it != (*m_stream).end())
		{
			ch = *m_it;
			++m_it;
		}
		return ch;
	};

	void Reset()
	{
		m_it = (*m_stream).begin();
	};

private:
	std::vector<char>* m_stream;
	std::vector<char>::iterator m_it = (*m_stream).begin();
};

// �����, ����������� ���������� IInputStream � IOutputStream
// ���������� ��� �������� ������ vector<char>, ������� � ������� ����������
// ������ � ������ ������������ ���������� ���� �� ����� (������� ������ � ������� ������ - ����)
// ������������� ������������� ������:
//   Clear() ������� ������ � ���������� ������� ������ � ������
//   ResetReadPos() - ���������� ������� ������, �� ����� ���������� �������
//   ResetWritePos() - ���������� ������� ������, �� ����� ���������� ������
//   ResetAll() - ���������� ��� �������, �� ����� ���������� �������
class MemoryStream : public IOutputStream
	, public IInputStream // �������� ����������� ���
{
	// �������� ����������� ���
public:
	void WriteChar(char ch) override
	{
		if (m_itWrite == m_stream.end())
		{
			try
			{
				m_stream.push_back(ch);
			}
			catch (std::exception&)
			{
				throw std::runtime_error("cant push_back element");
			}
			m_itWrite = m_stream.end();
		}
		else
		{
			*m_itWrite = ch;
			++m_itWrite;
		}
	};

	void Clear()
	{
		m_stream.clear();
		m_itWrite = m_stream.end();
		m_itRead = m_stream.end();
	};

	std::optional<char> Read() override
	{
		std::optional<char> ch = std::nullopt;
		if (m_itRead != m_stream.end())
		{
			ch = *m_itRead;
			++m_itRead;
		}
		return ch;
	};

	void ResetReadPos()
	{
		m_itRead = m_stream.begin();
	};

	void ResetWritePos()
	{
		m_itWrite = m_stream.begin();
	};

	void ResetAll()
	{
		m_itRead = m_stream.begin();
		m_itWrite = m_stream.begin();
	}

private:
	std::vector<char> m_stream = {};
	std::vector<char>::iterator m_itRead = m_stream.begin();
	std::vector<char>::iterator m_itWrite = m_stream.end();
};

// ���������� ������ � output �����������
void WriteString(IOutputStream& output, const std::string& s)
{
	// �������� ����������� ���
	for (auto ch : s)
	{
		output.WriteChar(ch);
	}
}

// ������ �� input ����������� � ������ �� �����
std::string ReadString(IInputStream& input)
{
	// �������� ����������� ���
	std::string rezult;
	while (std::optional<char> ch = input.Read())
	{
		rezult.push_back(*ch);
	}
	return rezult;
}

int main()
{
	// ������� ������
	// ��� ������ MemoryOutputStream �������� � ���� ����������� ���������� ������ hello = "hello"
	// ��� ������ MemoryInputStream ������� �� ���� ����������� ������ hello1
	// ���������, ��� ������ hello � hello1 ���������

	std::vector<char> stream;
	std::string hello = "hello";
	MemoryOutputStream outputStream(&stream);
	WriteString(outputStream, hello);
	MemoryInputStream inputStream(&stream);
	std::string hello1 = ReadString(inputStream);

	if (hello == hello1)
	{
		std::cout << "are equal" << std::endl;
	}
	else
	{
		std::cout << "not equal" << std::endl;
	}

	// C������ MemoryStream
	// �������� � ���� ����������� ������ goodbye = "Good bye"
	// ������� �� ���� ����������� ������ goodbye1
	// ���������� ������� ������ � �������� ������ "Must di"
	// ���������� ������� ������ � ������� �� ����� ����������
	// ���������, ��� ��������� "Must die"

	MemoryStream mStream;
	std::string goodbye = "Good bye";
	WriteString(mStream, goodbye);
	mStream.ResetReadPos();
	std::string goodbye1 = ReadString(mStream);

	if (goodbye == goodbye1)
	{
		std::cout << "are equal" << std::endl;
	}
	else
	{
		std::cout << "not equal" << std::endl;
	}

	std::string mustDi = "Must di";
	std::string mustDie = "Must die";

	mStream.ResetWritePos();
	WriteString(mStream, mustDi);
	mStream.ResetReadPos();
	std::string mustDie1 = ReadString(mStream);

	if (mustDie == mustDie1)
	{
		std::cout << "are equal" << std::endl;
	}
	else
	{
		std::cout << "not equal" << std::endl;
	}
}

