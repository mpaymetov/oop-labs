#include "stdafx.h"
#include "StringList.h"

CStringList::CStringList() noexcept
{
	m_firstNode = &m_endNode;
}

CStringList::CStringList(CStringList const& other)
{
	m_firstNode = &m_endNode;
	Node* otherTemp = other.m_firstNode;
	Node* newListTemp = nullptr;

	try
	{
		while (otherTemp->next)
		{
			Node* newNode = new Node(otherTemp->data, newListTemp, &m_endNode);

			if (m_size == 0)
			{
				m_firstNode = newNode;
			}
			else
			{
				newListTemp->next = newNode;
			}
			m_endNode.prev = newNode;
			++m_size;

			newListTemp = newNode;
			otherTemp = otherTemp->next;
		}
	}
	catch (std::exception&)
	{
		Clear();
		throw;
	}
}

CStringList::CStringList(CStringList&& other) noexcept
	: m_firstNode(other.m_firstNode)
	, m_size(other.m_size)
{
	if (m_size == 0)
	{
		m_firstNode = &m_endNode;
	}
	else
	{
		m_endNode.prev = other.m_endNode.prev;
		m_endNode.prev->next = &m_endNode;
	}

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
	CStringList copy(other);
	Clear();
	*this = std::move(copy);
	
	return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{
	m_firstNode = other.m_firstNode;
	m_size = other.m_size;

	if (m_size == 0)
	{
		m_firstNode = &m_endNode;
	}
	else
	{
		m_endNode.prev = other.m_endNode.prev;
		m_endNode.prev->next = &m_endNode;
	}

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

CStringList::const_iterator CStringList::cbegin() const
{
	return const_iterator(m_firstNode);
};

CStringList::const_iterator CStringList::cend() const
{
	return const_iterator(&m_endNode);
};

CStringList::reverse_iterator CStringList::rbegin()
{
	return reverse_iterator(iterator(&m_endNode));
}

CStringList::reverse_iterator CStringList::rend()
{
	return reverse_iterator(iterator(m_firstNode));
}

CStringList::reverse_const_iterator CStringList::crbegin() const
{
	return reverse_const_iterator(const_iterator(&m_endNode));
};

CStringList::reverse_const_iterator CStringList::crend() const
{
	return reverse_const_iterator(const_iterator(m_firstNode));
};

CStringList::iterator CStringList::Emplace(iterator pos, std::string const& str)
{
	Node* newNode = new Node(str, pos.m_node->prev, pos.m_node);
	
	if (newNode->prev == nullptr)
	{
		m_firstNode = newNode;
	}
	else
	{
		newNode->prev->next = newNode;
	}

	newNode->next->prev = newNode;
	++m_size;

	return iterator(newNode);
}

void CStringList::Remove(iterator pos)
{
	Node* temp = pos.m_node;
	if (temp->next == nullptr)
	{
		throw std::length_error("list is empty");
	}

	temp->next->prev = temp->prev;
	if (temp->prev == nullptr)
	{
		m_firstNode = temp->next;
	}
	else
	{
		temp->prev->next = temp->next;
	}
	--m_size;
}

