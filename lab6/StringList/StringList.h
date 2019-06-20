#pragma once
#include "stdafx.h"
//#include "iterator.h"

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
	CStringList();
	~CStringList();

	void PushFront(std::string& str);
	void PushBack(std::string& str);

	size_t GetSize() const noexcept;
	bool IsEmpty() const noexcept;
	void Clear() noexcept;

	//iterator Emplace(const_iterator pos, Args&& args);
	//void remove(const_iterator pos);

	//class CIterator
	//{
	//	friend CStringList;
	//	CIterator(Node* node);

	//public:
	//	CIterator() = default;
	//	std::string& operator*() const;
	//	CIterator& operator++();

	//private:
	//	Node* m_node = nullptr;
	//};

	//using iterator = CIterator<Node, false>;
	//using const_iterator = CIterator<Node, true>;

	//using reverse_iterator = std::reverse_iterator<iterator>;
	//using reverse_const_iterator = std::reverse_iterator<const_iterator>;

	//iterator begin();
	//iterator end();
	//iterator begin() const;
	//iterator end() const;
	//const_iterator cbegin() const;
	//const_iterator cend() const;

	//reverse_iterator rbegin();
	//reverse_iterator rend();
	//reverse_iterator rbegin() const;
	//reverse_iterator rend() const;
	//reverse_const_iterator crbegin() const;
	//reverse_const_iterator crend() const;

	std::string& GetBackElement();
	std::string const& GetBackElement() const;

	std::string& GetFrontElement();
	std::string const& GetFrontElement() const;

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode;
	Node* m_endNode;
};
