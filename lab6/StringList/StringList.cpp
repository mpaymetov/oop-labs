#include "stdafx.h"
#include "StringList.h"

CStringList::CStringList() noexcept
{
	m_firstNode = &m_endNode;
}

CStringList::CStringList(CStringList const& other)
{
	Node* firstNode = &m_endNode;
	Node* otherTemp = other.m_firstNode;
	Node* newListTemp = nullptr;
	size_t size = 0;

	while (otherTemp->next != nullptr)
	{
		Node* newNode = nullptr;
		try
		{
			newNode = new Node(otherTemp->data, newListTemp, nullptr);
		}
		catch (std::exception&)
		{
		}

		if (size == 0)
		{
			firstNode = newNode;
		}
		else
		{
			newListTemp->next = newNode;
		}

		newListTemp = newNode;
		++size;
		otherTemp = otherTemp->next;
	}

	if (size != 0)
	{
		m_firstNode = firstNode;
		m_endNode.prev = newListTemp;
		newListTemp->next = &m_endNode;
		m_size = size;
	}
}

CStringList::CStringList(CStringList&& other) noexcept
	: m_firstNode(other.m_firstNode)
	, m_size(other.m_size)
{
	m_endNode.prev = other.m_endNode.prev;
	m_endNode.prev->next = &m_endNode;

	other.m_firstNode = &other.m_endNode;
	other.m_endNode.prev = nullptr;
	other.m_size = 0;
}

CStringList::~CStringList() noexcept
{
	Clear();
}

void CStringList::PushFront(std::string const& str)
{
	Node* newNode = new Node(str, nullptr, m_firstNode);
	m_firstNode = newNode;
	m_firstNode->next->prev = m_firstNode;
	++m_size;
}

void CStringList::PushBack(std::string const& str)
{
	Node* newNode = new Node(str, m_endNode.prev, &m_endNode);
	if (m_size == 0)
	{
		m_firstNode = newNode;
	}
	else
	{
		newNode->prev->next = newNode;
	}
	m_endNode.prev = newNode;
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
	while (m_firstNode->next)
	{
		auto temp = m_firstNode;
		m_firstNode = m_firstNode->next;
		delete temp;
	}
	m_size = 0;
}

std::string& CStringList::GetBackElement()
{
	if (m_size == 0)
	{
		throw std::length_error("list is empty");
	}
	return m_endNode.prev->data;
}

std::string const& CStringList::GetBackElement() const
{
	if (m_size == 0)
	{
		throw std::length_error("list is empty");
	}
	return m_endNode.prev->data;
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

CStringList& CStringList::operator=(CStringList const& other)
{
	Node* firstNode = &m_endNode;
	Node* otherTemp = other.m_firstNode;
	Node* newListTemp = nullptr;
	size_t size = 0;

	while (otherTemp->next != nullptr)
	{
		Node* newNode = nullptr;
		try
		{
			newNode = new Node(otherTemp->data, newListTemp, nullptr);
		}
		catch (std::exception&)
		{
		}

		if (size == 0)
		{
			firstNode = newNode;
		}
		else
		{
			newListTemp->next = newNode;
		}

		newListTemp = newNode;
		++size;
		otherTemp = otherTemp->next;
	}

	Clear();

	if (size != 0)
	{
		m_firstNode = firstNode;
		m_endNode.prev = newListTemp;
		newListTemp->next = &m_endNode;
		m_size = size;
	}
	
	return *this;
}

CStringList& CStringList::operator=(CStringList&& other)
{
	m_firstNode = other.m_firstNode;
	m_size = other.m_size;

	m_endNode.prev = other.m_endNode.prev;
	m_endNode.prev->next = &m_endNode;

	other.m_firstNode = &other.m_endNode;
	other.m_endNode.prev = nullptr;
	other.m_size = 0;

	return *this;
}

CStringList::iterator CStringList::begin()
{
	return iterator(m_firstNode);
}

CStringList::iterator CStringList::end()
{
	return iterator(&m_endNode);
}

//CStringList::iterator CStringList::begin() const
//{
//	return const_iterator(m_firstNode);
//}
//
//CStringList::iterator CStringList::end() const
//{
//	return const_iterator(&m_endNode);
//}

//CStringList::const_iterator const CStringList::cbegin() const
//{
//	return const_iterator(m_firstNode);
//};
//
//CStringList::const_iterator const CStringList::cend() const
//{
//	return const_iterator(&m_endNode);
//};

//CStringList::reverse_iterator CStringList::rbegin()
//{
//	return reverse_iterator(iterator(m_endNode.prev));
//}
//
//CStringList::reverse_iterator CStringList::rend()
//{
//	return reverse_iterator(iterator(m_firstNode));
//}

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
