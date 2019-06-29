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

	std::string& GetBackElement();
	std::string const& GetBackElement() const;

	std::string& GetFrontElement();
	std::string const& GetFrontElement() const;

	CStringList& operator=(CStringList const& other);
	CStringList& operator=(CStringList&& other) noexcept;

	template <bool IsConst>
	class CIterator
	{
	private:
		friend CStringList;
		friend class CIterator<true>;

	public:
		using MyType = CIterator<IsConst>;
		using value_type = std::conditional_t<IsConst, const Node, Node>;
		using return_value_type = std::conditional_t<IsConst, const std::string, std::string>;
		using reference = return_value_type&;
		using pointer = value_type*;
		using difference_type = size_t;
		using iterator_category = std::random_access_iterator_tag;

		CIterator() = default;
		CIterator(const CIterator<false>& other)
			: m_node(other.m_node)
		{
		}

		reference& operator*() const
		{
			assert(m_node);
			assert(m_node->next);
			return m_node->data;
		}
		
		CIterator& operator++()
		{
			assert(m_node);
			assert(m_node->next);
			m_node = m_node->next;
			return *this;
		}

		CIterator& operator--()
		{
			assert(m_node);
			assert(m_node->prev);
			m_node = m_node->prev;
			return *this;
		}

		size_t const operator-(CIterator const& other) const
		{
			assert(m_node);
			assert(other.m_node);
			
			size_t result = 0;
			Node* temp = this->m_node;
			while ((temp != other.m_node) && temp)
			{
				temp = temp->prev;
				++result;
			}
			if (temp != other.m_node)
			{
				throw std::length_error("difference error");
			}
			return result;
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
		pointer m_node = nullptr;

		CIterator<IsConst>(pointer node)
			: m_node(node)
		{
		}
	};

	using iterator = CIterator<false>;
	using const_iterator = CIterator<true>;

	using reverse_iterator = std::reverse_iterator<iterator>;
	using reverse_const_iterator = std::reverse_iterator<const_iterator>;

	iterator begin();
	iterator end();

	const_iterator cbegin() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	reverse_iterator rend();

	reverse_const_iterator crbegin() const;
	reverse_const_iterator crend() const;

	iterator Emplace(iterator pos, std::string const& str);
	void Remove(iterator pos);

private:
	Node* m_firstNode;
	Node m_endNode = Node("", nullptr, nullptr);
	size_t m_size = 0;
};
