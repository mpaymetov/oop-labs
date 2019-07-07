#pragma once
#include "stdafx.h"
#include "Variable.h"
#include "Function.h"
#include "Operator.h"

class CCalculator
{
public:
	bool SetVar(const std::string& identifier, std::string& errorMsg);
	bool SetValue(const std::string& identifier, const double value, std::string& errorMsg);
	bool GetValue(const std::string& identifier, double& result, std::string& errorMsg) const;
	bool SetFn(const std::string& identifier, const std::string& firstOperand, COperator const& mathOperator, const std::string& secondOperand, std::string& errorMsg);
	std::map<std::string, double> GetAllVarsVales() const;
	std::map<std::string, double> GetAllFnsVales() const;

private:
	std::map<std::string, std::shared_ptr<IValueRetriever>> m_names;
	std::map<std::string, std::shared_ptr<CVariable>> m_vars;
	std::map<std::string, std::shared_ptr<CFunction>> m_fns;
	std::vector<std::shared_ptr<CFunction>> m_fnsUpdateList;

	void UpdateFns();
};
