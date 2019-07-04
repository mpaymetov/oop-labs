#include "stdafx.h"

#include <iostream>
#include <optional>
#include <string>
#include <vector>

// Интерфейс "Выходной поток данных", поддерживает операции
// Поддерживает операции:
//  WriteChar - выводит в поток символ
//  В случае ошибки бросает исключение std::runtime_error
class IOutputStream
{
public:
	virtual ~IOutputStream() = default;
	virtual void WriteChar(char ch) = 0;
	// Написать недостающий код
};

// Интерфейс "Входной поток данных", поддерживает операции
// Поддерживает операции:
//  Read - считывает символ из потока данных
//   Если поток закончился, возвращает "пустой" символ
//   В случае ошибки бросает исключение std::runtime_error
class IInputStream
{
public:
	virtual ~IInputStream() = default;
	virtual std::optional<char> Read() = 0;
	// Написать недостающий код
};

// Класс, реализующий интерфейс IOuputStream
// В качестве хранилища данных использует vector<char>, ссылка на который передаётся ему снаружи
// Внимание - векто
// Дополнительно предоставляет операции:
//   Clear(), очищающую массив и перематывающую в начало
//   Reset(), перематывает позицию записи в начало массива, не меняя его содержимое
class MemoryOutputStream : public IOutputStream // Написать недостающий код
{
	// Написать недостающий код
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

// Класс, реализующий интерфейс IInputStream
// В качестве источника данных использует vector<char>, ссылка на который передаётся ему снаружи
// Дополнительно предоставляет операцию Reset(), выполняющую перемотку в начало вектора
class MemoryInputStream : public IInputStream // Написать недостающий код
{
	// Написать недостающий код
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

// Класс, реализующий интерфейсы IInputStream и IOutputStream
// Использует для хранения массив vector<char>, которым и владеет единолично
// Чтение и запись производятся независимо друг от друга (позиция чтения и позиция записи - свои)
// Дополнительно предоставляет методы:
//   Clear() очищает массив и сбрасывает позиции чтения и записи
//   ResetReadPos() - сбрасывает позицию чтения, не меняя содержимое массива
//   ResetWritePos() - сбрасывает позицию записи, не меняя содержимое массив
//   ResetAll() - сбрасывает обе позиции, не меняя содержимое массива
class MemoryStream : public IOutputStream
	, public IInputStream // Написать недостающий код
{
	// Написать недостающий код
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

// Записывает строку в output посимвольно
void WriteString(IOutputStream& output, const std::string& s)
{
	// Написать недостающий код
	for (auto ch : s)
	{
		output.WriteChar(ch);
	}
}

// Читает из input посимвольно в строку до конца
std::string ReadString(IInputStream& input)
{
	// Написать недостающий код
	std::string rezult;
	while (std::optional<char> ch = input.Read())
	{
		rezult.push_back(*ch);
	}
	return rezult;
}

int main()
{
	// Создать массив
	// При помощи MemoryOutputStream записать в него посимвольно содержимое строки hello = "hello"
	// При помощи MemoryInputStream считать из него посимвольно строку hello1
	// Убедиться, что строки hello и hello1 одинаковы

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

	// Cоздать MemoryStream
	// Записать в него посимвольно строку goodbye = "Good bye"
	// Считать из него посимвольно строку goodbye1
	// Перемотать позицию записи и записать строку "Must di"
	// Перемотать позицию чтения и считать до конца содержимое
	// Убедиться, что прочитано "Must die"

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

