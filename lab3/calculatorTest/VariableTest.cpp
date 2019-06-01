#include "stdafx.h"
#include "../calculator/variable.h"

TEST_CASE("variable can have value")
{
	CVariable var;
	double result = var.GetValue();
	CHECK(std::isnan(result));
	var.SetValue(3.1415);
	result = var.GetValue();
	CHECK(!std::isnan(result));
	CHECK(result == 3.1415);
};