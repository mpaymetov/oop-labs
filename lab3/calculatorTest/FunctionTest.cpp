#include "stdafx.h"
#include "../calculator/function.h"

TEST_CASE("test create function with one operand")
{
	auto first = std::make_shared<CVariable>();
	CFunction fn(first);
	double result = fn.GetValue();
	CHECK(std::isnan(result));
	first->SetValue(3.1415);
	result = fn.GetValue();
	CHECK(!std::isnan(result));
	CHECK(result == 3.1415);
}

TEST_CASE("test create function with two operands")
{
	auto first = std::make_shared<CVariable>();
	auto second = std::make_shared<CVariable>();
	
	CFunction sum(first, COperator::Addition, second);
	CFunction mult(first, COperator::Multiplication, second);
	CFunction sub(first, COperator::Subtraction, second);
	CFunction div(first, COperator::Division, second);

	double sumResult = sum.GetValue();
	double multResult = mult.GetValue();
	double subResult = sub.GetValue();
	double divResult = div.GetValue();
	
	CHECK(std::isnan(sumResult));
	CHECK(std::isnan(multResult));
	CHECK(std::isnan(subResult));
	CHECK(std::isnan(divResult));
	
	first->SetValue(3);
	second->SetValue(4);
	
	sumResult = sum.GetValue();
	multResult = mult.GetValue();
	subResult = sub.GetValue();
	divResult = div.GetValue();

	CHECK(!std::isnan(sumResult));
	CHECK(!std::isnan(multResult));
	CHECK(!std::isnan(subResult));
	CHECK(!std::isnan(divResult));

	CHECK(sumResult == 7);
	CHECK(multResult == 12);
	CHECK(subResult == -1);
	CHECK(divResult == 0.75);
}

