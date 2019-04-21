#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx.h"

TEST_CASE("test FindMaxEx functon for int vector")
{
	std::vector<int> v = { 7, 5, 16, 8 };
	int result;
	CHECK(FindMax(v, result, std::less<int>()));
	CHECK(result == 16);
}

TEST_CASE("test FindMaxEx functon cant find int empty vector")
{
	std::vector<int> v;
	int result;
	CHECK(!FindMax(v, result, std::less<int>()));
}

TEST_CASE("test FindMaxEx functon for double vector")
{
	std::vector<double> v = { 7.1, 5.2, 16.3, 8.4 };
	double result;
	CHECK(FindMax(v, result, std::less<double>()));
	CHECK(result == 16.3);
}

TEST_CASE("test FindMaxEx functon for string vector")
{
	std::vector<std::string> v = { "one", "two", "three", "four"};
	std::string result;
	CHECK(FindMax(v, result, std::less<std::string>()));
	CHECK(result == "two");
}

class CSportsman
{
public:
	CSportsman(){};
	CSportsman(std::string name, unsigned char height, unsigned char weight)
		: m_name(name)
		, m_height(height)
		, m_weight(weight)
	{
	}
	std::string m_name;
	unsigned char m_height;
	unsigned char m_weight;
};

std::vector<CSportsman> sportsmans = {
	CSportsman("First", 175, 85),
	CSportsman("Second", 185, 75),
	CSportsman("Third", 180, 95)
};

TEST_CASE("Find sportsman with Max height")
{
	CSportsman result;
	CHECK(FindMax(sportsmans, result, [](CSportsman const& a, CSportsman const& b) {return a.m_height < b.m_height;}));
	CHECK(result.m_name == "Second");
	CHECK(result.m_height == 185);
}

TEST_CASE("Find sportsman with Max weight")
{
	CSportsman result;
	CHECK(FindMax(sportsmans, result, [](CSportsman const& a, CSportsman const& b) {return a.m_weight < b.m_weight;}));
	CHECK(result.m_name == "Third");
	CHECK(result.m_weight == 95);
}