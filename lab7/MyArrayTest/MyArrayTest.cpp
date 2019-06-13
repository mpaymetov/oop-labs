#include "stdafx.h"
#include "../MyArray/MyArray.h"

TEST_CASE("test create empty int MyArray variable")
{
	CMyArray<int> intArr;
	CHECK(intArr.GetSize() == 0);
}

TEST_CASE("test append to double MyArray variable")
{
	CMyArray<double> doubleArr;
	doubleArr.Append(1.25);
	CHECK(doubleArr.GetSize() == 1);
}

TEST_CASE("test append to int MyArray variable with change capacity")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	intArr.Append(3);
	intArr.Append(4);
	CHECK(intArr.GetSize() == 4);
}

TEST_CASE("test MyArray operator []")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	CHECK(intArr.GetSize() == 2);
	CHECK(intArr[0] == 1);
	intArr[0] = 3;
	CHECK(intArr[0] == 3);
	CHECK_THROWS_AS(intArr[3] = 4, std::out_of_range);
}

TEST_CASE("test MyArray const operator []")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	CHECK(intArr.GetSize() == 2);
	int i = intArr[0];
	CHECK(i == 1);
	CHECK_THROWS_AS(i = intArr[3], std::out_of_range);
}

TEST_CASE("test clear MyArray variable")
{
	CMyArray<int> intArr;
	intArr.Append(25);
	CHECK(intArr.GetSize() == 1);
	intArr.Clear();
	CHECK(intArr.GetSize() == 0);
}

TEST_CASE("test copy constructor MyArray")
{
	CMyArray<double> doubleArr;
	doubleArr.Append(1.25);
	CMyArray<double> second(doubleArr);
	CHECK(second.GetSize() == 1);
	CHECK(second[0] == 1.25);
}

TEST_CASE("test MyArray move constructor")
{
	CMyArray<int> intArr;
	intArr.Append(25);
	CMyArray<int> second(std::move(intArr));
	CHECK(second.GetSize() == 1);
	CHECK(second[0] == 25);
}

TEST_CASE("test MyArray operator copy =")
{
	CMyArray<int> first;
	first.Append(1);
	first.Append(2);

	CMyArray<int> second;
	second = first;
	CHECK(second[0] == 1);
	CHECK(second[1] == 2);
	CHECK(second.GetSize() == 2);
}

TEST_CASE("test MyArray operator move =")
{
	CMyArray<int> first;
	first.Append(1);
	first.Append(2);

	CMyArray<int> second;
	second = std::move(first);
	CHECK(second[0] == 1);
	CHECK(second[1] == 2);
	CHECK(second.GetSize() == 2);
}

TEST_CASE("test MyArray resize if new size < current")
{
	CMyArray<int> first;
	first.Append(1);
	first.Append(2);
	first.Append(3);
	first.Append(4);
	first.Append(5);

	CHECK(first.GetSize() == 5);
	first.Resize(3);
	CHECK(first.GetSize() == 3);
}

TEST_CASE("test MyArray resize if new size > current && < capacity")
{
	CMyArray<int> first;
	first.Append(1);
	first.Append(2);
	first.Append(3);
	first.Append(4);
	first.Append(5);

	CHECK(first.GetSize() == 5);
	CHECK(first.GetCapacity() == 8);
	first.Resize(7);
	CHECK(first.GetSize() == 7);
	CHECK(first[4] == 5);
	CHECK(first[5] == 0);
	CHECK(first[6] == 0);
}

TEST_CASE("test MyArray resize if new size > capacity")
{
	CMyArray<int> first;
	first.Append(1);
	first.Append(2);
	first.Append(3);
	first.Append(4);

	CHECK(first.GetSize() == 4);
	CHECK(first.GetCapacity() == 4);
	first.Resize(6);
	CHECK(first.GetSize() == 6);
	CHECK(first[3] == 4);
	CHECK(first[4] == 0);
	CHECK(first[5] == 0);
}

TEST_CASE("test MyArray method begin()")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	auto it = intArr.begin();
	CHECK(*it == 1);
}

TEST_CASE("test MyArray postfix increment")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	auto it = intArr.begin();
	CHECK(*it == 1);
	it++;
	CHECK(*it == 2);
}

TEST_CASE("test MyArray prefix increment")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	auto it = intArr.begin();
	CHECK(*it == 1);
	++it;
	CHECK(*it == 2);
}

TEST_CASE("test MyArray method end(), prefix & postfix decrement")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	auto it = intArr.end();
	--it;
	CHECK(*it == 2);
	it--;
	CHECK(*it == 1);
}

TEST_CASE("test MyArray method rbegin()")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	auto it = intArr.rbegin();
	CHECK(*it == 2);
	it++;
	CHECK(*it == 1);
}

TEST_CASE("test MyArray method rend()")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	auto it = intArr.rend();
	--it;
	CHECK(*it == 1);
	it--;
	CHECK(*it == 2);
}

TEST_CASE("test MyArray iterator + offset")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	intArr.Append(3);
	auto it = intArr.begin();
	CHECK(*it == 1);
	CHECK(*(it + 2) == 3);
}

TEST_CASE("test MyArray offset + iterator")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	intArr.Append(3);
	auto it = intArr.begin();
	CHECK(*it == 1);
	CHECK(*(2 + it) == 3);
}

TEST_CASE("test MyArray iterator += offset")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	intArr.Append(3);
	auto it = intArr.begin();
	CHECK(*it == 1);
	it += 2;
	CHECK(*it == 3);
}

TEST_CASE("test MyArray iterator operator[]")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	intArr.Append(3);
	auto it = intArr.begin();
	CHECK(*it == 1);
	CHECK(it[2] == 3);
}

TEST_CASE("test MyArray iterator operator=")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	intArr.Append(3);
	auto it = intArr.begin();
	auto newIt = intArr.end();
	newIt = it;
	CHECK(*newIt == 1);
}

struct two_int_nums
{
	int first;
	int second;
};

TEST_CASE("test MyArray iterator operator->")
{
	two_int_nums nums = { 1, 2 };
	CMyArray<two_int_nums> arr;
	arr.Append(nums);
	auto it = arr.begin();
	CHECK(it->first == 1);
	CHECK(it->second == 2);
}

TEST_CASE("test MyArray iterator operator-=")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	auto it = intArr.end();
	it -= 2;
	CHECK(*it == 1);
}

TEST_CASE("test MyArray iterator operator - offset")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	auto it = intArr.end();
	auto newIt = it - 2;
	CHECK(*newIt == 1);
}

TEST_CASE("test MyArray iterator operator-")
{
	CMyArray<int> intArr;
	intArr.Append(1);
	intArr.Append(2);
	auto itBegin = intArr.begin();
	auto itEnd = intArr.end();
	auto offset = itEnd - itBegin;
	CHECK(offset == 2);
}

TEST_CASE("test MyArray of string")
{
	CMyArray<std::string> strArr;
	std::string first = "first";
	std::string second = "second";
	std::string third = "third";
	strArr.Append(first);
	strArr.Append(second);
	strArr.Append(third);

	CHECK(strArr[0] == "first");
	CHECK(strArr[1] == "second");
	CHECK(strArr[2] == "third");

	auto it = strArr.begin();
	CHECK(*it == "first");
	CHECK(*(it + 1) == "second");
	CHECK(it[2] == "third");

	it++;
	CHECK(*it == "second");

	int i = 0;
	for (auto it = strArr.begin(); it < strArr.end(); ++it)
	{
		CHECK(*it == strArr[i]);
		++i;
	}

	i = 0;
	for (auto str : strArr)
	{
		CHECK(str == strArr[i]);
		++i;
	}

	CMyArray<std::string> arrCopy;
	arrCopy.Resize(strArr.GetSize());
	std::copy(strArr.begin(), strArr.end(), arrCopy.begin());
	CHECK(arrCopy[2] == "third");
}

TEST_CASE("test MyArray copy to const iterator")
{
	CMyArray<int> arr;
	arr.Append(5);
	CMyArray<int>::iterator it = arr.begin();
	
	CMyArray<int>::const_iterator cit;
	cit = it;
	auto num = *cit;
	CHECK(num == 5);
}

TEST_CASE("test MyArray iterator operator==")
{
	CMyArray<int> arr;
	arr.Append(5);
	arr.Append(6);
	CMyArray<int>::iterator it1 = arr.begin();
	CMyArray<int>::iterator it2 = arr.begin();
	CMyArray<int>::iterator it3 = arr.end();
	CHECK(it1 == it2);
	CHECK(!(it1 == it3));
}

TEST_CASE("test MyArray iterator operator>")
{
	CMyArray<int> arr;
	arr.Append(5);
	arr.Append(6);
	CMyArray<int>::iterator it1 = arr.begin();
	CMyArray<int>::iterator it2 = arr.begin();
	CMyArray<int>::iterator it3 = arr.end();
	CHECK(!(it1 > it2));
	CHECK(!(it1 > it3));
	CHECK(it3 > it2);
}

TEST_CASE("test MyArray iterator operator>=")
{
	CMyArray<int> arr;
	arr.Append(5);
	arr.Append(6);
	CMyArray<int>::iterator it1 = arr.begin();
	CMyArray<int>::iterator it2 = arr.begin();
	CMyArray<int>::iterator it3 = arr.end();
	CHECK(it1 >= it2);
	CHECK(!(it1 >= it3));
	CHECK(it3 >= it2);
}

TEST_CASE("test MyArray iterator operator<=")
{
	CMyArray<int> arr;
	arr.Append(5);
	arr.Append(6);
	CMyArray<int>::iterator it1 = arr.begin();
	CMyArray<int>::iterator it2 = arr.begin();
	CMyArray<int>::iterator it3 = arr.end();
	CHECK(it1 <= it2);
	CHECK(it1 <= it3);
	CHECK(!(it3 <= it2));
}

