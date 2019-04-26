#include "stdafx.h"
#include "Variable.h"

bool CVariable::HaveValue() const
{
	return m_isSet;
}

double CVariable::GetValue() const
{
	return m_value;
}

void CVariable::SetValue(double value)
{
	m_value = value;
	m_isSet = true;
}