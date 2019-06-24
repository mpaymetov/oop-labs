#pragma once
#include "stdafx.h"
#include <assert.h>

class Node
{
public:
	Node(const std::string& data, Node* prev, Node* next)
		: data(data)
		, prev(prev)
		, next(next)
	{
	}
	std::string data;
	Node* prev;
	Node* next;
};

class CStringList
{
public:
	CStringList() noexcept;
	CStringList(CStringList const& other);
	CStringList(CStringList&& other) noexcept;
	~CStringList() noexcept;

	void PushFront(std::string const& str);
	void PushBack(std::string const& str);

	size_t GetSize() const noexcept;
	bool IsEmpty() const noexcept;
	void Clear() noexcept;

	CStringList& operator=(CStringList const& other);
	CStringList& operator=(CStringList&& other);


	//iterator Emplace(const_iterator pos, Args&& args);
	//void remove(const_iterator pos);

	template <bool IsConst>
	class CIterator
	{
	private:
		friend CStringList;
		friend class CIterator<true>;
		CIterator(Node* node)
			: m_node(node)
		{
		}

	public:
		using MyType = CIterator<IsConst>;
		using value_type = std::conditional_t<IsConst, const Node, Node>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		CIterator() = default;
		CIterator(const CIterator<false>& other)
			: m_node(other.m_node)
		{
		}

		std::string& operator*() const
		{
			assert(m_node->next);
			return m_node->data;
		}

		CIterator& operator++()
		{
			assert(m_node->next);
			m_node = m_node->next;
			return *this;
		}

		CIterator& operator--()
		{
			assert(m_node->prev);
			m_node = m_node->prev;
			return *this;
		}

		bool operator==(CIterator const& other) const
		{
			return m_node == other.m_node;
		}

		bool operator!=(CIterator const& other) const
		{
			return m_node != other.m_node;
		}


	private:
		Node* m_node = nullptr;
	};

	using iterator = CIterator<false>;
	using const_iterator = CIterator<true>;

	using reverse_iterator = std::reverse_iterator<iterator>;
	using reverse_const_iterator = std::reverse_iterator<const_iterator>;

	iterator begin();
	iterator end();
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
	Node* m_firstNode = nullptr;
	Node m_endNode = Node("", nullptr, nullptr);
	size_t m_size = 0;
};
