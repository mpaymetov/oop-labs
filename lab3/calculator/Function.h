#pragma once
#include "ValueRetriever.h"
#include "Variable.h"
#include "Operator.h"

class CFunction : public IValueRetriever
{
public:
	CFunction(std::shared_ptr<IValueRetriever> first, COperator mathOperator = COperator::Undefined, std::shared_ptr<IValueRetriever> second = nullptr);

	double GetValue() const override;
	bool HaveValue() const override;

	void SetParams(std::shared_ptr<IValueRetriever> first, COperator mathOperator = COperator::Undefined, std::shared_ptr<IValueRetriever> second = nullptr);

private:
	std::shared_ptr<IValueRetriever> m_firstOperand;
	std::shared_ptr<IValueRetriever> m_secondOperand;
	COperator m_operator;
};
