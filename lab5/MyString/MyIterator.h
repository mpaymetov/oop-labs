#pragma once
#include <assert.h>

template <typename T, bool IsConst>
class CMyIterator
{
private:
	friend class CMyString;
	friend class CMyIterator<T, true>;

	CMyIterator(T* ptr)
		: m_ptr(ptr)
	{
	}

public:
	using MyType = CMyIterator<T, IsConst>;
	using value_type = std::conditional_t<IsConst, const T, T>;
	using reference = value_type&;
	using pointer = value_type*;
	using difference_type = ptrdiff_t;
	using iterator_category = std::random_access_iterator_tag;

	CMyIterator() = default;
	CMyIterator(const CMyIterator<T, false>& other)
		: m_ptr(other.m_ptr)
	{
	}

	reference& operator*() const
	{
		assert(m_ptr);
		return *m_ptr;
	}

	reference& operator[](ptrdiff_t index) const
	{
		assert(m_ptr);
		return *(m_ptr + index);
	}

	CMyIterator& operator++()
	{
		assert(m_ptr);
		++m_ptr;
		return *this;
	}

	CMyIterator& operator+=(ptrdiff_t offset)
	{
		assert(m_ptr);
		m_ptr += offset;
		return *this;
	}

	CMyIterator const operator++(int)
	{
		assert(m_ptr);
		CMyIterator copy(*this);
		++m_ptr;
		return copy;
	}

	CMyIterator const operator+(ptrdiff_t offset) const
	{
		assert(m_ptr);
		auto newPtr = m_ptr + offset;
		return CMyIterator(newPtr);
	}

	CMyIterator& operator--()
	{
		assert(m_ptr);
		--m_ptr;
		return *this;
	}

	CMyIterator& operator-=(ptrdiff_t offset)
	{
		assert(m_ptr);
		m_ptr -= offset;
		return *this;
	}

	CMyIterator const operator--(int)
	{
		assert(m_ptr);
		CMyIterator copy(*this);
		--m_ptr;
		return copy;
	}

	CMyIterator const operator-(ptrdiff_t offset) const
	{
		assert(m_ptr);
		auto newPtr = m_ptr - offset;
		return CMyIterator(newPtr);
	}

	ptrdiff_t const operator-(CMyIterator const& other) const
	{
		assert(m_ptr);
		assert(other.m_ptr);
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

template <typename T, bool IsConst>
CMyIterator<T, IsConst> operator+(ptrdiff_t offset, CMyIterator<T, IsConst> const& it)
{
	auto copy = it;
	copy += offset;
	return copy;
}

