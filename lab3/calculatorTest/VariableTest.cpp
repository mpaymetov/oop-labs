#include "stdafx.h"
#include "../calculator/variable.h"

TEST_CASE("variable can have value")
{
	CVariable var;
	CHECK(!var.HaveValue());
	var.SetValue(3.1415);
	CHECK(var.HaveValue());
	CHECK(var.GetValue() == 3.1415);
};