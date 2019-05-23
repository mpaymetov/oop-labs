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

CMyArray<int> ReturnCopy(CMyArray<int>& other)
{
	CMyArray<int> copy(other);
	return copy;
}

TEST_CASE("test MyArray move constructor")
{
	CMyArray<int> intArr;
	intArr.Append(25);
	CMyArray<int> second = ReturnCopy(intArr);
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
	second = ReturnCopy(first);
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
