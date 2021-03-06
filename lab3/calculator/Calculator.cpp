#include "stdafx.h"
#include "calculator.h"
#include "Function.h"
#include "Variable.h"

bool CanBeIdentifier(const std::string& identifier)
{
	if (identifier.empty())
	{
		return false;
	}

	if (!std::isalpha(identifier[0]) && (identifier[0] != '_'))
	{
		return false;
	}

	for (auto& ch : identifier)
	{
		if (!std::isalpha(ch) && (ch != '_') && (!std::isdigit(ch)))
		{
			return false;
		}
	}

	return true;
}

bool CCalculator::SetVar(const std::string& identifier, std::string& errorMsg)
{
	if (!CanBeIdentifier(identifier))
	{
		errorMsg = "identifier name incorrect";
		return false;
	}

	if (auto it = m_names.find(identifier); it != m_names.end())
	{
		errorMsg = "identifier already exist";
		return false;
	}

	auto var = std::make_pair(identifier, std::make_shared<CVariable>());
	m_names.insert(var);
	m_vars.insert(var);
	return true;
}

bool CCalculator::SetValue(const std::string& identifier, const double value, std::string& errorMsg)
{
	if (!CanBeIdentifier(identifier))
	{
		errorMsg = "identifier name incorrect";
		return false;
	}

	std::pair<std::string, std::shared_ptr<CVariable>> var;
	if (auto it = m_names.find(identifier); it != m_names.end())
	{
		auto it2 = m_vars.find(identifier);
		var = *it2;
	}
	else
	{
		var = std::make_pair(identifier, std::make_shared<CVariable>());
		m_names.insert(var);
		m_vars.insert(var);
	}

	var.second->SetValue(value);
	UpdateFns();
	return true;
}

bool CCalculator::GetValue(const std::string& identifier, double& result, std::string& errorMsg) const
{
	if (auto it = m_names.find(identifier); it != m_names.end())
	{
		auto var = *it;
		result = var.second->GetValue();
		return true;
	}

	errorMsg = "identifier not exist";
	return false;
}

bool CCalculator::SetFn(const std::string& identifier, const std::string& firstOperand, COperator const& mathOperator, const std::string& secondOperand, std::string& errorMsg)
{
	if (!CanBeIdentifier(identifier))
	{
		errorMsg = "identifier name incorrect";
		return false;
	}

	if (auto it = m_fns.find(identifier); it != m_fns.end())
	{
		errorMsg = "function already exist";
		return false;
	}
	
	std::shared_ptr<IValueRetriever> first, second = nullptr;
	
	if (auto it = m_names.find(firstOperand); it != m_names.end())
	{
		first = it->second;
	}
	else
	{
		errorMsg = "Error: first operand not exist";
		return false;
	}

	if (auto it = m_names.find(secondOperand); it != m_names.end())
	{
		second = it->second;
	}
	else if (mathOperator != COperator::Undefined)
	{
		errorMsg = "Error: second operand not exist";
		return false;
	}

	//auto fnLink = std::make_shared<CFunction>(first, mathOperator, second);
	auto fn = std::make_pair(identifier, std::make_shared<CFunction>(first, mathOperator, second));
	
	m_names.insert(fn);
	m_fns.insert(fn);
	m_fnsUpdateList.push_back(fn.second);
	
	return true;
}

std::map<std::string, double> CCalculator::GetAllVarsVales() const
{
	std::map<std::string, double> vars;

	for (const auto& [name, val] : m_vars)
	{
		vars.emplace(name, val->GetValue());
	}

	return vars;
}

std::map<std::string, double> CCalculator::GetAllFnsVales() const
{
	std::map<std::string, double> fns;

	for (const auto& [name, val] : m_fns)
	{
		fns.emplace(name, val->GetValue());
	}

	return fns;
}

void CCalculator::UpdateFns()
{
	for (auto& fn : m_fnsUpdateList)
	{
		fn->Update();
	}
}

