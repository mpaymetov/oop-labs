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