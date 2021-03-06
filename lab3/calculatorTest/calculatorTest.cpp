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

TEST_CASE("calculator test Get All Vars Vales")
{
	CCalculator calculator;
	std::string errorMsg;
	std::map<std::string, double> vars;
	vars.insert({ "x", 5.4 });
	vars.insert({ "y", 6.2 });

	CHECK(calculator.SetValue("x", 5.4, errorMsg));
	CHECK(calculator.SetValue("y", 6.2, errorMsg));
	auto result = calculator.GetAllVarsVales();

	auto it1 = result.begin();
	auto it2 = vars.begin();
	CHECK(it1->first == it2->first);
	CHECK(it1->second == it2->second);

	++it1;
	++it2;
	CHECK(it1->first == it2->first);
	CHECK(it1->second == it2->second);
}

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

TEST_CASE("calculator test Get All fns Vales")
{
	CCalculator calculator;
	std::string errorMsg;
	std::map<std::string, double> fns;
	fns.insert({ "xplusy", 11.6 });

	CHECK(calculator.SetValue("x", 5.4, errorMsg));
	CHECK(calculator.SetValue("y", 6.2, errorMsg));
	calculator.SetFn("xplusy", "x", COperator::Addition, "y", errorMsg);
	auto result = calculator.GetAllFnsVales();

	auto it1 = result.begin();
	auto it2 = fns.begin();
	CHECK(it1->first == it2->first);
	CHECK((it1->second - it2->second) < 0.0001);
}

