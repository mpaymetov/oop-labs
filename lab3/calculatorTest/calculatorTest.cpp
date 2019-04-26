#include "stdafx.h"
#include "../calculator/variable.h"
#include "../calculator/calculator.h"

TEST_CASE("calculator can create variable, if not exist")
{
	CCalculator calculator;
	CHECK(calculator.SetVar("x"));
	CHECK(!calculator.SetVar("x"));
	CHECK(!calculator.SetVar("1x"));
	CHECK(calculator.SetVar("x2"));
};

TEST_CASE("calculator can set value to variable")
{
	CCalculator calculator; 
	std::string result;
	CHECK(!calculator.GetValue("x", result));
	CHECK(calculator.SetVar("x"));
	CHECK(calculator.GetValue("x", result));
	CHECK(result == "nan");
	
	CHECK(calculator.SetValue("x", "3.1234"));
	CHECK(calculator.GetValue("x", result));
	CHECK(result == "3.12");
};

TEST_CASE("calculator can set value to variable without setvar")
{
	CCalculator calculator;
	std::string result;
	CHECK(calculator.SetValue("x", "3.1234"));
	CHECK(calculator.GetValue("x", result));
	CHECK(result == "3.12");
};

TEST_CASE("calculator can not set value to variable if varname or value incorrect")
{
	CCalculator calculator;
	CHECK(!calculator.SetValue("1x", "3.1234"));
	CHECK(!calculator.SetValue("x", "sdf"));
}

TEST_CASE("calculator can set value to variable from other vars")
{
	CCalculator calculator;
	std::string result;
	CHECK(calculator.SetValue("x", "3.1234"));
	CHECK(calculator.SetValue("y", "x"));
	CHECK(calculator.GetValue("y", result));
	CHECK(result == "3.12");
	}

TEST_CASE("calculator test Get All Vars Vales")
{
	CCalculator calculator;
	CHECK(calculator.SetVar("x"));
	CHECK(calculator.SetVar("y"));
	CHECK(calculator.SetVar("z"));
	CHECK(calculator.SetValue("x", "5.4"));
	CHECK(calculator.SetValue("y", "6.2"));
	std::string result = calculator.GetAllVarsVales();
	CHECK(result == "x: 5.4\ny: 6.2\nz: nan\n");
}

TEST_CASE("calculator test create function")
{
	CCalculator calculator;
	std::string result;
	CHECK(calculator.SetVar("x"));
	CHECK(calculator.SetVar("y"));
	CHECK(calculator.SetFn("sum", "x", "+", "y"));
	CHECK(calculator.GetValue("sum", result));
	CHECK(result == "nan");

	CHECK(calculator.SetValue("x", "2"));
	CHECK(calculator.SetValue("y", "3"));
	CHECK(calculator.GetValue("sum", result));
	CHECK(result == "5");
}

TEST_CASE("calculator can not create function with error in params")
{
	CCalculator calculator;
	CHECK(!calculator.SetFn("fn", "x", "", ""));
	calculator.SetVar("x");
	CHECK(!calculator.SetFn("1fn", "x", "", ""));
}

TEST_CASE("calculator test create function with one operand")
{
	CCalculator calculator;
	std::string result;
	CHECK(calculator.SetVar("x"));
	CHECK(calculator.SetFn("fn", "x", "", ""));
	CHECK(calculator.GetValue("fn", result));
	CHECK(result == "nan");

	CHECK(calculator.SetValue("x", "2"));
	CHECK(calculator.GetValue("fn", result));
	CHECK(result == "2");
}

TEST_CASE("calculator test change functions params")
{
	CCalculator calculator;
	std::string result;
	CHECK(calculator.SetValue("a", "2"));
	CHECK(calculator.SetValue("b", "3"));
	CHECK(calculator.SetFn("fn", "a", "*", "b"));
	CHECK(calculator.GetValue("fn", result));
	CHECK(result == "6");

	CHECK(calculator.SetValue("c", "8"));
	CHECK(calculator.SetValue("d", "2"));
	CHECK(calculator.SetFn("fn", "c", "/", "d"));
	CHECK(calculator.GetValue("fn", result));
	CHECK(result == "4");

	CHECK(calculator.SetValue("e", "5"));
	CHECK(calculator.SetValue("f", "3"));
	CHECK(calculator.SetFn("fn", "e", "-", "f"));
	CHECK(calculator.GetValue("fn", result));
	CHECK(result == "2");
}

TEST_CASE("calculator test Get All fns Vales")
{
	CCalculator calculator;
	calculator.SetVar("x");
	calculator.SetVar("y");
	calculator.SetVar("z");
	calculator.SetValue("x", "5");
	calculator.SetValue("y", "4");
	calculator.SetFn("abc", "x", "+", "y");
	calculator.SetFn("bcd", "x", "-", "z");
	std::string result = calculator.GetAllFnsVales();

	CHECK(result == "abc: 9\nbcd: nan\n");
}