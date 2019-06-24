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

