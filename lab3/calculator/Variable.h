#pragma once
#include "ValueRetriever.h"
#include "Operator.h"

class CVariable : public IValueRetriever
{
public:
	double GetValue() const override;
	bool HaveValue() const override;

	void SetValue(double value);
	
private:
	double m_value;
	bool m_isSet = false;
};
