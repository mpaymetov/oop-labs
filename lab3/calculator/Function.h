#pragma once
#include "ValueRetriever.h"
#include "Variable.h"
#include "Operator.h"

class CFunction : public IValueRetriever
{
public:
	CFunction(std::shared_ptr<IValueRetriever> first, COperator mathOperator, std::shared_ptr<IValueRetriever> second);
	CFunction(std::shared_ptr<IValueRetriever> first);

	double GetValue() const override;
	void Update();

private:
	std::shared_ptr<IValueRetriever> m_firstOperand;
	std::shared_ptr<IValueRetriever> m_secondOperand;
	COperator m_operator;

	double m_value = std::nan("1");
};
