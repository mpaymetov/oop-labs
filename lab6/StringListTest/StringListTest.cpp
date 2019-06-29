#include "stdafx.h"
#include "../StringList/StringList.h"

TEST_CASE("test StringList create empty")
{
	CStringList list;
	CHECK(list.GetSize() == 0);
	CHECK(list.IsEmpty());
}

TEST_CASE("test StringList PushFront & GetFrontElement")
{
	CStringList list;

	std::string first = "Hello";
	list.PushFront(first);
	CHECK(list.GetSize() == 1);
	CHECK(list.GetFrontElement() == first);

	std::string second = "World";
	list.PushFront(second);
	CHECK(list.GetSize() == 2);
	CHECK(list.GetFrontElement() == second);
}

TEST_CASE("test StringList PushBack & GetBackElement")
{
	CStringList list;

	std::string first = "Hello";
	list.PushBack(first);
	CHECK(list.GetSize() == 1);
	CHECK(list.GetBackElement() == first);
	CHECK(list.GetFrontElement() == first);

	std::string second = "World";
	list.PushBack(second);
	CHECK(list.GetSize() == 2);
	CHECK(list.GetBackElement() == second);
	CHECK(list.GetFrontElement() == first);
}

TEST_CASE("test StringList IsEmpty, GetSize & Clear")
{
	CStringList list;
	CHECK(list.IsEmpty());
	CHECK(list.GetSize() == 0);

	std::string first = "Hello";
	list.PushBack(first);
	CHECK(!list.IsEmpty());
	CHECK(list.GetSize() == 1);

	std::string second = "World";
	list.PushBack(second);
	CHECK(list.GetSize() == 2);
	CHECK(!list.IsEmpty());

	list.Clear();
	CHECK(list.IsEmpty());
	CHECK(list.GetSize() == 0);
}

TEST_CASE("test StringList exception for empty list")
{
	CStringList list;
	CHECK_THROWS_AS(list.GetBackElement(), std::length_error);
	CHECK_THROWS_AS(list.GetFrontElement(), std::length_error);
}

TEST_CASE("test StringList copy constructor")
{
	CStringList list;
	std::string first = "Hello";
	list.PushFront(first);
	std::string second = "World";
	list.PushBack(second);

	CStringList newList = list;
	CHECK(newList.GetSize() == 2);
	CHECK(newList.GetFrontElement() == first);
	CHECK(newList.GetBackElement() == second);
}

TEST_CASE("test StringList copy operator=")
{
	CStringList list;
	std::string first = "Hello";
	list.PushFront(first);
	std::string second = "World";
	list.PushBack(second);

	CStringList newList;
	newList = list;
	CHECK(newList.GetSize() == 2);
	CHECK(newList.GetFrontElement() == first);
	CHECK(newList.GetBackElement() == second);
}

TEST_CASE("test StringList move constructor")
{
	CStringList list;
	std::string first = "Hello";
	list.PushFront(first);
	std::string second = "World";
	list.PushBack(second);

	CStringList newList = std::move(list);
	CHECK(list.GetSize() == 0);
	CHECK(newList.GetSize() == 2);
	CHECK(newList.GetFrontElement() == first);
	CHECK(newList.GetBackElement() == second);
}

TEST_CASE("test StringList move operator=")
{
	CStringList list;
	std::string first = "Hello";
	list.PushFront(first);
	std::string second = "World";
	list.PushBack(second);

	CStringList newList;
	newList = std::move(list);
	CHECK(list.GetSize() == 0);
	CHECK(newList.GetSize() == 2);
	CHECK(newList.GetFrontElement() == first);
	CHECK(newList.GetBackElement() == second);
}

TEST_CASE("test StringList iterator begin & end")
{
	CStringList list;
	std::string first = "Hello";
	list.PushFront(first);
	CStringList::iterator it = list.begin();
	CHECK(*it == first);

	std::string second = "World";
	list.PushBack(second);
	CStringList::iterator endIt = list.end();
	--endIt;
	CHECK(*endIt == second);
}

TEST_CASE("test StringList iterator operator for")
{
	CStringList list;
	std::string first = "Hello";
	list.PushFront(first);
	std::string second = "World";
	list.PushBack(second);

	std::vector<std::string> vstr;
	vstr.push_back(first);
	vstr.push_back(second);

	int i = 0;
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		CHECK(*it == vstr[i]);
		++i;
	}
}

TEST_CASE("test StringList iterator operator range based for")
{
	CStringList list;
	std::string first = "Hello";
	list.PushFront(first);
	std::string second = "World";
	list.PushBack(second);

	std::vector<std::string> vstr;
	vstr.push_back(first);
	vstr.push_back(second);

	int i = 0;
	for (auto it : list)
	{
		CHECK(it == vstr[i]);
		++i;
	}
}

//TEST_CASE("test StringList iterator stl algorithm")
//{
//	CStringList list;
//	std::string first = "Hello";
//	list.PushFront(first);
//	std::string second = "World";
//	list.PushBack(second);
//
//	std::vector<std::string> testVector;
//	testVector.push_back(first);
//	testVector.push_back(second);
//
//	std::vector<std::string> toVector(list.GetSize());
//
//	std::copy(list.begin(), list.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

	//int i = 0;
	//for (auto it : toVector)
	//{
	//	CHECK(it == testVector[i]);
	//	++i;
	//}
//}

TEST_CASE("test StringList Emplace to front")
{
	CStringList list;
	std::string first = "Hello";
	list.PushFront(first);
	std::string second = "World";
	list.PushBack(second);

	CStringList::iterator it = list.begin();
	CHECK(*it == first);

	std::string newStr = "new";
	list.Emplace(it, newStr);

	it = list.begin();
	CHECK(*it == newStr);
	++it;
	CHECK(*it == first);
	++it;
	CHECK(*it == second);
}

TEST_CASE("test StringList Emplace")
{
	CStringList list;
	std::string first = "Hello";
	list.PushFront(first);
	std::string second = "World";
	list.PushBack(second);

	CStringList::iterator it = list.begin();
	++it;
	CHECK(*it == second);

	std::string newStr = "new";
	list.Emplace(it, newStr);

	it = list.begin();
	CHECK(*it == first);
	++it;
	CHECK(*it == newStr);
	++it;
	CHECK(*it == second);
}

TEST_CASE("test StringList Remove")
{
	CStringList list;
	std::string first = "Hello";
	list.PushBack(first);
	std::string strToRemove = "strToRemove";
	list.PushBack(strToRemove);
	std::string second = "World";
	list.PushBack(second);

	CStringList::iterator it = list.begin();
	CHECK(*it == first);
	++it;
	CHECK(*it == strToRemove);
	++it;
	CHECK(*it == second);

	it = list.begin();
	++it;
	CHECK(*it == strToRemove);
	list.Remove(it);

	it = list.begin();
	CHECK(*it == first);
	++it;
	CHECK(*it == second);
}

//TEST_CASE("test StringList revers iterator begin & end")
//{
//	CStringList list;
//	std::string first = "Hello";
//	list.PushFront(first);
//	std::string second = "World";
//	list.PushBack(second);
//
//	CStringList::reverse_iterator it = list.rbegin();
//	std::string test = *it;
//	CHECK(*it == second);
//	++it;
//	CHECK(*it == first);
//}
//






