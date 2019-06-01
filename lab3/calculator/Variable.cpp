#include "stdafx.h"
#include "Variable.h"

double CVariable::GetValue() const
{
	return m_value;
}

void CVariable::SetValue(double value)
{
	m_value = value;
}
