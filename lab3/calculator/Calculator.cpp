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

	auto it = m_names.find(identifier);
	if (it == m_names.end())
	{
		auto val = std::make_shared<CVariable>();
		auto var = std::make_pair(identifier, val);
		m_names.insert(var);
		m_vars.insert(var);
		return true;
	}

	errorMsg = "identifier already exist";
	return false;
}

bool CCalculator::SetValue(const std::string& identifier, const double value, std::string& errorMsg)
{
	if (!CanBeIdentifier(identifier))
	{
		errorMsg = "identifier name incorrect";
		return false;
	}

	std::pair<std::string, std::shared_ptr<CVariable>> var;

	auto it = m_vars.find(identifier);
	if (it != m_vars.end())
	{
		var = *it;
	}
	else
	{
		var = std::make_pair(identifier, std::make_shared<CVariable>());
		m_names.insert(var);
		m_vars.insert(var);
	}

	var.second->SetValue(value);
	return true;
}

bool CCalculator::GetValue(const std::string& identifier, double& result, std::string& errorMsg) const
{
	auto it = m_names.find(identifier);
	if (it != m_names.end())
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

	auto it = m_fns.find(identifier);
	if (it != m_fns.end())
	{
		errorMsg = "function already exist";
		return false;
	}
	
	std::shared_ptr<IValueRetriever> first, second = nullptr;
	auto it_var = m_names.find(firstOperand);
	if (it_var != m_names.end())
	{
		first = it_var->second;
	}
	else
	{
		errorMsg = "Error: first operand not exist";
		return false;
	}

	it_var = m_names.find(secondOperand);
	if (it_var != m_names.end())
	{
		second = it_var->second;
	}
	else if (mathOperator != COperator::Undefined)
	{
		errorMsg = "Error: second operand not exist";
		return false;
	}

	auto fn = std::make_pair(identifier, std::make_shared<CFunction>(first, mathOperator, second));
	//fn.second->Update();
	m_names.insert(fn);
	m_fns.insert(fn);
	return true;
}

std::map<std::string, double> CCalculator::GetAllVarsVales() const
{
	std::map<std::string, double> vars;

	for (const auto& [name, val] : m_vars)
	{
		auto var = std::make_pair(name, val->GetValue());
		vars.emplace(var);
	}

	return vars;
}

std::map<std::string, double> CCalculator::GetAllFnsVales() const
{
	std::map<std::string, double> fns;

	for (const auto& [name, val] : m_fns)
	{
		auto var = std::make_pair(name, val->GetValue());
		fns.emplace(var);
	}

	return fns;
}

