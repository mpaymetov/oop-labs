#include "stdafx.h"
#include "StringList.h"

CStringList::CStringList()
{
	m_firstNode = std::make_unique<Node>("", nullptr, nullptr);
	m_lastNode = m_firstNode.get();
	m_endNode = m_lastNode;
}

CStringList::~CStringList() noexcept
{
	Clear();
}

void CStringList::PushFront(std::string& str)
{
	auto newNode = std::make_unique<Node>(str, nullptr, std::move(m_firstNode));
	m_firstNode = std::move(newNode);
	m_firstNode->next->prev = m_firstNode.get();

	if (m_size == 0)
	{
		m_lastNode = m_firstNode.get();
	}
	
	++m_size;
}

void CStringList::PushBack(std::string& str)
{
	auto newNode = std::make_unique<Node>(str, m_endNode->prev, nullptr);
	if (m_size == 0)
	{
		newNode->next = std::move(m_firstNode);
		m_firstNode = std::move(newNode);
		m_lastNode = m_firstNode.get();
	}
	else
	{
		newNode->next = std::move(m_lastNode->next);
		m_lastNode->next = std::move(newNode);
		m_lastNode = m_lastNode->next.get();
	}
	m_endNode->prev = m_lastNode;
	++m_size;
}

size_t CStringList::GetSize() const noexcept
{
	return m_size;
}

bool CStringList::IsEmpty() const noexcept
{
	return m_size == 0;
}

void CStringList::Clear() noexcept
{
	if (m_size != 0)
	{
		m_firstNode = std::move(m_lastNode->next);
		m_lastNode = m_endNode;
		m_size = 0;
	}
}

std::string& CStringList::GetBackElement()
{
	if (m_size == 0)
	{
		throw std::length_error("list is empty");
	}
	return m_lastNode->data;
}

std::string const& CStringList::GetBackElement() const
{
	if (m_size == 0)
	{
		throw std::length_error("list is empty");
	}
	return m_lastNode->data;
}

std::string& CStringList::GetFrontElement()
{
	if (m_size == 0)
	{
		throw std::length_error("list is empty");
	}
	return m_firstNode->data;
}

std::string const& CStringList::GetFrontElement() const
{
	if (m_size == 0)
	{
		throw std::length_error("list is empty");
	}
	return m_firstNode->data;
}

//CStringList::iterator CStringList::begin()
//{
//	return iterator(m_firstNode.get());
//}
//
//CStringList::iterator CStringList::end()
//{
//	return iterator(m_lastNode);
//}
//
//CStringList::iterator CStringList::begin() const
//{
//	return const_iterator(m_begin);
//}
//
//CStringList::iterator CStringList::end() const
//{
//	return const_iterator(m_end);
//}
//
//CStringList::const_iterator const CStringList::cbegin() const
//{
//	return const_iterator(m_begin);
//};
//
//CStringList::const_iterator const CStringList::cend() const
//{
//	return const_iterator(m_end);
//};
//
//CStringList::reverse_iterator CStringList::rbegin()
//{
//	return reverse_iterator(iterator(m_end));
//}
//
//CStringList::reverse_iterator CStringList::rend()
//{
//	return reverse_iterator(iterator(m_begin));
//}
//
//CStringList::reverse_iterator CStringList::rbegin() const
//{
//	return reverse_const_iterator(const_iterator(m_end));
//}
//
//CStringList::reverse_iterator CStringList::rend() const
//{
//	return reverse_const_iterator(const_iterator(m_begin));
//}
//
//CStringList::reverse_const_iterator const CStringList::crbegin() const
//{
//	return reverse_const_iterator(const_iterator(m_end));
//};
//
//CStringList::reverse_const_iterator const CStringList::crend() const
//{
//	return reverse_const_iterator(const_iterator(m_begin));
//};

