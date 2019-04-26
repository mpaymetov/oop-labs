#include "stdafx.h"
#include "Function.h"

CFunction::CFunction(std::shared_ptr<IValueRetriever> first, COperator mathOperator, std::shared_ptr<IValueRetriever> second)
	: m_firstOperand(first)
	, m_secondOperand(second)
	, m_operator(mathOperator)
{
}

double CFunction::GetValue() const
{
	double result = 0;
	switch (m_operator)
	{
		case COperator::Addition: 
		{
			if (m_firstOperand->HaveValue() && m_secondOperand->HaveValue())
			{
				result = m_firstOperand->GetValue() + m_secondOperand->GetValue();
			};
			break;
		}
		case COperator::Subtraction: 
		{

			if (m_firstOperand->HaveValue() && m_secondOperand->HaveValue())
			{
				result = m_firstOperand->GetValue() - m_secondOperand->GetValue();
			};
			break;
		}
		case COperator::Multiplication: 
		{
			if (m_firstOperand->HaveValue() && m_secondOperand->HaveValue())
			{
				result = m_firstOperand->GetValue() * m_secondOperand->GetValue();
			};
			break;
		}
		case COperator::Division: 
		{
			if (m_firstOperand->HaveValue() && m_secondOperand->HaveValue())
			{
				result = m_firstOperand->GetValue() / m_secondOperand->GetValue();
			};
			break;
		}
		case COperator::Undefined: 
		{
			if (m_firstOperand->HaveValue())
			{
				result = m_firstOperand->GetValue();
			};
			break;
		}
	}

	return result;
}

bool CFunction::HaveValue() const
{
	bool haveValue;
	if (m_operator == COperator::Undefined)
	{
		haveValue = m_firstOperand->HaveValue();
	}
	else
	{
		haveValue = m_firstOperand->HaveValue() && m_secondOperand->HaveValue();
	}
	return haveValue;
}

void CFunction::SetParams(std::shared_ptr<IValueRetriever> first, COperator mathOperator, std::shared_ptr<IValueRetriever> second)
{
	m_firstOperand = first;
	m_operator = mathOperator;
	m_secondOperand = second;
}
