#pragma once
#include "stdafx.h"
#include "MyIterator.h"

class CMyString
{
public:
	CMyString() noexcept;
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other) noexcept;
	CMyString(std::string const& stlString);

	~CMyString() noexcept;

	CMyString& operator=(CMyString const& other);
	CMyString& operator=(CMyString&& other) noexcept;
	CMyString& operator+=(CMyString const& other);
	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	size_t GetLength() const noexcept;
	const char* GetStringData() const noexcept;

	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	friend CMyString const operator+(CMyString const& string1, CMyString const& string2);

	void Clear() noexcept;

	using iterator = CMyIterator<char, false>;
	using const_iterator = CMyIterator<char, true>;

	using reverse_iterator = std::reverse_iterator<iterator>;
	using reverse_const_iterator = std::reverse_iterator<const_iterator>;

	iterator begin();
	iterator end();

	const_iterator const cbegin() const;
	const_iterator const cend() const;

	reverse_iterator rbegin();
	reverse_iterator rend();

	reverse_const_iterator const crbegin() const;
	reverse_const_iterator const crend() const;

private:
	CMyString(size_t size);

	char* m_chars;
	size_t m_length;
};

bool const operator==(CMyString const& string1, CMyString const& string2);
bool const operator!=(CMyString const& string1, CMyString const& string2);
bool const operator<(CMyString const& string1, CMyString const& string2);
bool const operator>(CMyString const& string1, CMyString const& string2);
bool const operator<=(CMyString const& string1, CMyString const& string2);
bool const operator>=(CMyString const& string1, CMyString const& string2);

std::ostream& operator<<(std::ostream& strm, CMyString const& myStr);
std::istream& operator>>(std::istream& strm, CMyString& myStr);
