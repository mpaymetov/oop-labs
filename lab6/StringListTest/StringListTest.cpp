#include "stdafx.h"
#include "../StringList/StringList.h"

TEST_CASE("test StringList create empty")
{
	CStringList list;
	CHECK(list.GetSize() == 0);
	CHECK(list.IsEmpty());
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

TEST_CASE("test StringList IsEmpty")
{
	CStringList list;
	CHECK(list.IsEmpty());

	std::string first = "Hello";
	list.PushBack(first);
	CHECK(!list.IsEmpty());
}

TEST_CASE("test StringList PushFront")
{
	CStringList list;

	std::string first = "Hello";
	list.PushFront(first);
	CHECK(list.GetSize() == 1);
	CHECK(list.GetFrontElement() == first);
	CHECK(list.GetBackElement() == first);

	std::string second = "World";
	list.PushFront(second);
	CHECK(list.GetSize() == 2);
	CHECK(list.GetFrontElement() == second);
	CHECK(list.GetBackElement() == first);
}

TEST_CASE("test StringList exception for empty list")
{
	CStringList list;
	CHECK_THROWS_AS(list.GetBackElement(), std::length_error);
	CHECK_THROWS_AS(list.GetFrontElement(), std::length_error);
}

TEST_CASE("test StringList iterator begin")
{
	CStringList list;
	std::string first = "Hello";
	list.PushFront(first);
	CStringList::iterator it = list.begin();
	std::string test = *it;
	CHECK(test == first);
}

