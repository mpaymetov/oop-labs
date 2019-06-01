#include "stdafx.h"
#include "../calculator/variable.h"
#include "../calculator/calculator.h"

TEST_CASE("calculator can create variable, if not exist")
{
	CCalculator calculator;
	std::string errorMsg;
	CHECK(calculator.SetVar("x", errorMsg));
	CHECK(!calculator.SetVar("x", errorMsg));
	CHECK(!calculator.SetVar("1x", errorMsg));
	CHECK(calculator.SetVar("x2", errorMsg));
}

TEST_CASE("calculator can set value to variable")
{
	CCalculator calculator;
	std::string errorMsg;
	double result;
	CHECK(!calculator.GetValue("x", result, errorMsg));
	CHECK(calculator.SetVar("x", errorMsg));
	CHECK(calculator.GetValue("x", result, errorMsg));
	CHECK(std::isnan(result));
	
	CHECK(calculator.SetValue("x", 3.1234, errorMsg));
	CHECK(calculator.GetValue("x", result, errorMsg));
	CHECK(!std::isnan(result));
	CHECK(result == 3.1234);
}

TEST_CASE("calculator can set value to variable without setvar")
{
	CCalculator calculator;
	std::string errorMsg;
	double result;
	CHECK(calculator.SetValue("x", 3.1234, errorMsg));
	CHECK(calculator.GetValue("x", result, errorMsg));
	CHECK(!std::isnan(result));
	CHECK(result == 3.1234);
}

TEST_CASE("calculator can not set value to variable if varname incorrect")
{
	CCalculator calculator;
	std::string errorMsg;
	CHECK(!calculator.SetValue("1x", 3.1234, errorMsg));
}

//TEST_CASE("calculator test Get All Vars Vales")
//{
//	CCalculator calculator;
//	CHECK(calculator.SetVar("x"));
//	CHECK(calculator.SetVar("y"));
//	CHECK(calculator.SetVar("z"));
//	CHECK(calculator.SetValue("x", "5.4"));
//	CHECK(calculator.SetValue("y", "6.2"));
//	std::string result = calculator.GetAllVarsVales();
//	CHECK(result == "x: 5.4\ny: 6.2\nz: nan\n");
//}

TEST_CASE("calculator test create function")
{
	CCalculator calculator;
	std::string errorMsg;
	double result;
	CHECK(calculator.SetVar("x", errorMsg));
	CHECK(calculator.SetVar("y", errorMsg));
	CHECK(calculator.SetFn("sum", "x", COperator::Addition, "y", errorMsg));
	CHECK(calculator.GetValue("sum", result, errorMsg));
	CHECK(std::isnan(result));

	CHECK(calculator.SetValue("x", 2, errorMsg));
	CHECK(calculator.SetValue("y", 3, errorMsg));
	CHECK(calculator.GetValue("sum", result, errorMsg));
	CHECK(result == 5);
}

TEST_CASE("calculator can not create function with error in params")
{
	CCalculator calculator;
	std::string errorMsg;
	CHECK(!calculator.SetFn("fn", "x", COperator::Undefined, "", errorMsg));
	calculator.SetVar("x", errorMsg);
	CHECK(!calculator.SetFn("1fn", "x", COperator::Undefined, "", errorMsg));
}

TEST_CASE("calculator test create function with one operand")
{
	CCalculator calculator;
	std::string errorMsg;
	double result;
	CHECK(calculator.SetVar("x", errorMsg));
	CHECK(calculator.SetFn("fn", "x", COperator::Undefined, "", errorMsg));
	CHECK(calculator.GetValue("fn", result, errorMsg));
	CHECK(std::isnan(result));

	CHECK(calculator.SetValue("x", 2, errorMsg));
	CHECK(calculator.GetValue("fn", result, errorMsg));
	CHECK(result == 2);
}

TEST_CASE("calculator test can not change functions params")
{
	CCalculator calculator;
	std::string errorMsg;
	double result;
	CHECK(calculator.SetValue("a", 2, errorMsg));
	CHECK(calculator.SetValue("b", 3, errorMsg));
	CHECK(calculator.SetFn("fn", "a", COperator::Multiplication, "b", errorMsg));
	CHECK(calculator.GetValue("fn", result, errorMsg));
	CHECK(!std::isnan(result));
	CHECK(result == 6);

	CHECK(calculator.SetValue("c", 8, errorMsg));
	CHECK(calculator.SetValue("d", 2, errorMsg));
	CHECK(!calculator.SetFn("fn", "c", COperator::Division, "d", errorMsg));
	CHECK(calculator.GetValue("fn", result, errorMsg));
	CHECK(result == 6);
}

//TEST_CASE("calculator test Get All fns Vales")
//{
//	CCalculator calculator;
//	calculator.SetVar("x");
//	calculator.SetVar("y");
//	calculator.SetVar("z");
//	calculator.SetValue("x", "5");
//	calculator.SetValue("y", "4");
//	calculator.SetFn("abc", "x", "+", "y");
//	calculator.SetFn("bcd", "x", "-", "z");
//	std::string result = calculator.GetAllFnsVales();
//
//	CHECK(result == "abc: 9\nbcd: nan\n");
//}