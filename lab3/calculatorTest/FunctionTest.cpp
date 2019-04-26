#include "stdafx.h"
#include "../calculator/function.h"

TEST_CASE("test create function with one operand")
{
	auto first = std::make_shared<CVariable>();
	CFunction fn(first);
	CHECK(!fn.HaveValue());
	first->SetValue(3.1415);
	CHECK(fn.HaveValue());
	CHECK(fn.GetValue() == 3.1415);
}

TEST_CASE("test create function with two operands")
{
	auto first = std::make_shared<CVariable>();
	auto second = std::make_shared<CVariable>();
	
	CFunction sum(first, COperator::Addition, second);
	CFunction mult(first, COperator::Multiplication, second);
	CFunction sub(first, COperator::Subtraction, second);
	CFunction div(first, COperator::Division, second);
	
	CHECK(!sum.HaveValue());
	CHECK(!mult.HaveValue());
	CHECK(!sub.HaveValue());
	CHECK(!div.HaveValue());
	
	first->SetValue(3);
	second->SetValue(4);
	
	CHECK(sum.HaveValue());
	CHECK(mult.HaveValue());
	CHECK(sub.HaveValue());
	CHECK(div.HaveValue());

	CHECK(sum.GetValue() == 7);
	CHECK(mult.GetValue() == 12);
	CHECK(sub.GetValue() == -1);
	CHECK(div.GetValue() == 0.75);
}

TEST_CASE("test function change params")
{
	auto first = std::make_shared<CVariable>();
	auto second = std::make_shared<CVariable>();
	auto third = std::make_shared<CVariable>();
	auto fourth = std::make_shared<CVariable>();

	first->SetValue(1);
	second->SetValue(2);
	third->SetValue(3);
	fourth->SetValue(4);

	CFunction fn(first, COperator::Addition, second);
	CHECK(fn.GetValue() == 3);

	fn.SetParams(third, COperator::Division, fourth);
	CHECK(fn.GetValue() == 0.75);
}