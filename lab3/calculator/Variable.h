#pragma once
#include "ValueRetriever.h"

class CVariable : public IValueRetriever
{
public:
	double GetValue() const override;
	void SetValue(double value);

private:
	double m_value = std::nan("1");
};
