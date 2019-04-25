#include "stdafx.h"
#include "Function.h"

double CFunction::GetValue() const
{
	return 0;
}

bool CFunction::HaveValue() const
{
	return true;
}

std::string CFunction::GetType() const
{
	return "fn";
}
