#pragma once
#include "ValueRetriever.h"
#include "Variable.h"
#include "Operator.h"

class CFunction : public IValueRetriever
{
public:
	double GetValue() const override;
	bool HaveValue() const override;

	std::string GetType() const override;

private:
	std::shared_ptr<IValueRetriever> m_firstOperand = nullptr;
	std::shared_ptr<IValueRetriever> n_secondOperand = nullptr;
	COperator m_operator = COperator::Undefined;
};
