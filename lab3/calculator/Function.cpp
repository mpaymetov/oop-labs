#include "stdafx.h"
#include "Function.h"

CFunction::CFunction(std::shared_ptr<IValueRetriever> first, COperator mathOperator, std::shared_ptr<IValueRetriever> second)
	: m_firstOperand(first)
	, m_secondOperand(second)
	, m_operator(mathOperator)
{
	Update();
}

CFunction::CFunction(std::shared_ptr<IValueRetriever> first)
	: m_firstOperand(first)
	, m_secondOperand(nullptr)
	, m_operator(COperator::Undefined)
{
	Update();
}

double CFunction::GetValue() const
{
	return m_value;
}

void CFunction::Update()
{
	double val1 = m_firstOperand->GetValue();
	if (!std::isnan(val1))
	{
		switch (m_operator)
		{
			case COperator::Addition:
			{
				double val2 = m_secondOperand->GetValue();
				if (!std::isnan(val2))
				{
					m_value = val1 + val2;
				}
				break;
			}
			case COperator::Subtraction:
			{
				double val2 = m_secondOperand->GetValue();
				if (!std::isnan(val2))
				{
					m_value = val1 - val2;
				}
				break;
			}
			case COperator::Multiplication:
			{
				double val2 = m_secondOperand->GetValue();
				if (!std::isnan(val2))
				{
					m_value = val1 * val2;
				}
				break;
			}
			case COperator::Division:
			{
				double val2 = m_secondOperand->GetValue();
				if (!std::isnan(val2) && (val2 != 0))
				{
					m_value = val1 / val2;
				}
				break;
			}
			case COperator::Undefined:
			{
				m_value = val1;
				break;
			}
		}
	}
}

