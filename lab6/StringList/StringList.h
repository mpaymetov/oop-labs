#pragma once
#include "stdafx.h"

class Node
{
public:
	Node(const std::string& data, Node* prev, std::unique_ptr<Node>&& next)
		: data(data)
		, prev(prev)
		, next(std::move(next))
	{
	}
	std::string data;
	Node* prev;
	std::unique_ptr<Node> next;
};

class CStringList
{
public:

	void PushFront(std::string& str);
	void PushBack(std::string& str);
	
	size_t GetSize() const;
	void Clear();
	
	iterator Emplace(const_iterator pos, Args&& args);
	void remove(const_iterator pos);

	class CIterator
	{
		friend CStringList;
		CIterator(Node* node);

	public:
		CIterator() = default;
		std::string& operator*() const;
		CIterator& operator++();

	private:
		Node* m_node = nullptr;
	};

	CIterator begin();

	std::string& GetBackElement();
	std::string const& GetBackElement() const;

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode = nullptr;
};

