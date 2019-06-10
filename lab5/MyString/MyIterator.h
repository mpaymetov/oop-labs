#pragma once
#include <assert.h>

template <typename T, bool IsConst>
class CMyIterator
{
private:
	template <typename T>
	friend class CMyArray;
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
//		assert(m_ptr);
		return *m_ptr;
	}

	pointer operator->() const
	{
//		assert(m_ptr);
		return &(operator*());
	}

	reference& operator[](ptrdiff_t index) const
	{
//		assert(m_ptr + index);
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
//		assert(m_ptr);
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
//		assert(m_ptr);
		return copy;
	}

	CMyIterator const operator+(ptrdiff_t offset) const
	{
		auto newPtr = m_ptr + offset;
//		assert(newPtr);
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
//		assert(m_ptr);
		return *this;
	}

	CMyIterator const operator--(int)
	{
		CMyIterator copy(*this);
		--m_ptr;
//		assert(m_ptr);
		return copy;
	}

	CMyIterator const operator-(ptrdiff_t offset) const
	{
		auto newPtr = m_ptr - offset;
//		assert(newPtr);
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

