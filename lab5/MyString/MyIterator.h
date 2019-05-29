#pragma once
#include <assert.h>

template <typename T>
class CMyIterator : public std::iterator<std::random_access_iterator_tag, T>
{
private:
	friend class CMyString;

	CMyIterator(T* ptr)
		: m_ptr(ptr)
	{
	}

public:
	CMyIterator()
	{
	}

	CMyIterator(const CMyIterator& it)
		: m_ptr(it.m_ptr)
	{
	}

	T& operator*() const
	{
		assert(m_ptr);
		return *m_ptr;
	}

	T* operator->() const
	{
		assert(m_ptr);
		return &(operator*());
	}

	T& operator[](ptrdiff_t index) const
	{
		assert(m_ptr + index);
		return *(m_ptr + index);
	}

	CMyIterator& operator=(const CMyIterator& it)
	{
		m_ptr = it.m_ptr;
		return *this;
	}

	CMyIterator& operator++()
	{
		++m_ptr;
		assert(m_ptr);
		return *this;
	}

	CMyIterator& operator+=(ptrdiff_t offset)
	{
		m_ptr += offset;
		return *this;
	}

	CMyIterator const operator++(int)
	{
		CMyIterator copy(*this);
		++m_ptr;
		assert(m_ptr);
		return copy;
	}

	CMyIterator const operator+(ptrdiff_t offset) const
	{
		auto newPtr = m_ptr + offset;
		assert(newPtr);
		return CMyIterator(newPtr);
	}

	CMyIterator& operator--()
	{
		--m_ptr;
		return *this;
	}

	CMyIterator& operator-=(ptrdiff_t offset)
	{
		m_ptr -= offset;
		assert(m_ptr);
		return *this;
	}

	CMyIterator const operator--(int)
	{
		CMyIterator copy(*this);
		--m_ptr;
		assert(m_ptr);
		return copy;
	}

	CMyIterator const operator-(ptrdiff_t offset) const
	{
		auto newPtr = m_ptr - offset;
		assert(newPtr);
		return CMyIterator(newPtr);
	}

	ptrdiff_t const operator-(CMyIterator const& other) const
	{
		ptrdiff_t result = m_ptr - other.m_ptr;
		return result;
	}

	bool operator==(CMyIterator const& other) const
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(CMyIterator const& other) const
	{
		return m_ptr != other.m_ptr;
	}

	bool operator<(CMyIterator const& other) const
	{
		return m_ptr < other.m_ptr;
	}

	bool operator>(CMyIterator const& other) const
	{
		return m_ptr > other.m_ptr;
	}

	bool operator<=(CMyIterator const& other) const
	{
		return m_ptr <= other.m_ptr;
	}

	bool operator>=(CMyIterator const& other) const
	{
		return m_ptr >= other.m_ptr;
	}

private:
	T* m_ptr = nullptr;
};

