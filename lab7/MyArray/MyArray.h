#pragma once
#include "stdafx.h"

template <typename T>
class CMyArray
{
public:
	CMyArray() = default;

	CMyArray(const CMyArray& arr)
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}

	CMyArray(CMyArray&& arr)
		: m_begin(arr.m_begin)
		, m_end(arr.m_end)
		, m_endOfCapacity(arr.m_endOfCapacity)
	{
		arr.m_begin = nullptr;
		arr.m_end = nullptr;
		arr.m_endOfCapacity = nullptr;
	}

	void Append(const T& value)
	{
		if (m_end == m_endOfCapacity)
		{
			size_t newCapacity = std::max(size_t(1), GetCapacity() * 2);

			auto newBegin = RawAlloc(newCapacity);
			T* newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				new (newEnd) T(value);
				++newEnd;
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else
		{
			new (m_end) T(value);
			++m_end;
		}
	}

	size_t GetCapacity() const noexcept
	{
		return m_endOfCapacity - m_begin;
	}

	size_t GetSize() const noexcept
	{
		return m_end - m_begin;
	}

	T& operator[](size_t index)
	{
		if (index >= GetSize())
		{
			throw std::out_of_range("index is out of range");
		}

		return m_begin[index];
	}

	const T& operator[](size_t index) const
	{
		if (index >= GetSize())
		{
			throw std::out_of_range("index is out of range");
		}

		return m_begin[index];
	}

	void Resize(size_t newSize)
	{
		if (newSize < GetSize())
		{
			DestroyItems(m_begin + newSize, m_end);
			m_end = m_begin + newSize;
		}
		else if ((newSize > GetSize()) && (newSize <= GetCapacity()))
		{
			auto newEnd = m_end;
			try
			{
				while (newEnd < m_begin + newSize)
				{
					new (newEnd) T();
					++newEnd;
				}
				m_end = newEnd;
			}
			catch (...)
			{
				DestroyItems(m_end, newEnd);
				throw;
			}
		}
		else if (newSize > GetCapacity())
		{
			auto newBegin = RawAlloc(newSize);
			auto newEnd = newBegin;
			auto m_endOfCapacity = newBegin + newSize;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				while (newEnd < m_endOfCapacity)
				{
					new (newEnd) T();
					++newEnd;
				}
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}

			DeleteItems(m_begin, m_end);

			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_endOfCapacity;
		}
	}

	void Clear()
	{
		DestroyItems(m_begin, m_end);
		m_end = m_begin;
	}

	CMyArray& operator=(CMyArray const& rhs)
	{
		if (m_begin != rhs.m_begin)
		{
			CMyArray newArr(rhs);

			std::swap(m_begin, newArr.m_begin);
			std::swap(m_end, newArr.m_end);
			std::swap(m_endOfCapacity, newArr.m_endOfCapacity);
		}
		return *this;
	}

	CMyArray& operator=(CMyArray&& rhs)
	{
		if (m_begin != rhs.m_begin)
		{
			Clear();
			m_begin = rhs.m_begin;
			m_end = rhs.m_end;
			m_endOfCapacity = rhs.m_endOfCapacity;

			rhs.m_begin = nullptr;
			rhs.m_end = nullptr;
			rhs.m_endOfCapacity = nullptr;
		}
		return *this;
	}

	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}

private:
	static void DeleteItems(T* begin, T* end)
	{
		DestroyItems(begin, end);
		RawDealloc(begin);
	}

	static void CopyItems(const T* srcBegin, T* srcEnd, T* const dstBegin, T*& dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			// Construct "T" at "dstEnd" as a copy of "*begin"
			new (dstEnd) T(*srcBegin);
		}
	}

	static void DestroyItems(T* from, T* to)
	{
		// dst - адрес объект, при конструирование которого было выброшено исключение
		// to - первый скорнструированный объект
		while (to != from)
		{
			--to;
			to->~T();
		}
	}

	static T* RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T* p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T* p)
	{
		free(p);
	}

private:
	T* m_begin = nullptr;
	T* m_end = nullptr;
	T* m_endOfCapacity = nullptr;
};
