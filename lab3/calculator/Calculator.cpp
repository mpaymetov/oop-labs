#include "stdafx.h"
#include "calculator.h"
#include "Function.h"
#include "Variable.h"

bool CCalculator::SetVar(const std::string& identifier)
{
	try
	{
		int i = std::stoi(identifier);
		m_error = Error::IDENTIFIER_NAME_INCORRECT;
		return false;
	}
	catch (const std::exception&)
	{
	}

	auto it = m_names.find(identifier);

	if (it == m_names.end())
	{
		auto val = std::make_shared<CVariable>();
		auto var = std::make_pair(identifier, val);
		m_names.insert(var);
		m_vars.insert(var);
		m_error = Error::NO_ERROR;
		return true;
	}

	m_error = Error::VARIABLE_ALREADY_EXISTS;
	return false;
}

bool CCalculator::SetValue(const std::string& identifier, const std::string& valueStr)
{
	std::pair<std::string, std::shared_ptr<CVariable>> var;

	auto it = m_vars.find(identifier);
	if (it != m_vars.end())
	{
		var = *it;
	}
	else
	{
		try
		{
			int i = std::stoi(identifier);
			m_error = Error::IDENTIFIER_NAME_INCORRECT;
			return false;
		}
		catch (const std::exception&)
		{
		}

		var = std::make_pair(identifier, std::make_shared<CVariable>());
		m_names.insert(var);
		m_vars.insert(var);
	}

	double value;	
	auto it2 = m_names.find(valueStr);
	if (it2 != m_names.end())
	{
		auto varValue = *it2;
		if (varValue.second->HaveValue())
		{
			value = varValue.second->GetValue();
		}
		else
		{			
			return true;
		}
	}
	else
	{
		try
		{
			value = std::stod(valueStr);
		}
		catch (const std::exception&)
		{
			m_error = Error::VALUE_INCORRECT;
			return false;
		}
	}

	var.second->SetValue(value);
	return true;
}

bool CCalculator::GetValue(const std::string& identifier, std::string& result)
{
	auto it = m_names.find(identifier);
	if (it != m_names.end())
	{
		auto var = *it;
		if (var.second->HaveValue())
		{
			double value = var.second->GetValue();
			std::ostringstream strs;
			strs << std::setprecision(3) << value;
			result = strs.str();
		}
		else
		{
			result = "nan";
		}
		m_error = Error::NO_ERROR;
		return true;
	}

	m_error = Error::VARIABLE_NOT_EXIST;
	return false;
}

bool CCalculator::SetFn(const std::string& identifier, const std::string& firstOperand, const std::string& mathOperatorStr, const std::string& secondOperand)
{
	std::shared_ptr<IValueRetriever> first, second;
	auto it_var = m_names.find(firstOperand);
	if (it_var != m_names.end())
	{
		first = it_var->second;
	}
	else
	{
		m_error = Error::VARIABLE_NOT_EXIST;
		return false;
	}
	
	auto mathOperator = GetMathOperator(mathOperatorStr);

	it_var = m_names.find(secondOperand);
	if (it_var != m_names.end())
	{
		second = it_var->second;
	}
	else
	{
		second = nullptr;
	}

	auto it = m_fns.find(identifier);
	if (it != m_fns.end())
	{
		auto fn = *it;
		fn.second->SetParams(first, mathOperator, second);
	}
	else
	{
		try
		{
			int i = std::stoi(identifier);
			m_error = Error::IDENTIFIER_NAME_INCORRECT;
			return false;
		}
		catch (const std::exception&)
		{
		}

		auto fn = std::make_pair(identifier, std::make_shared<CFunction>(first, mathOperator, second));
		m_names.insert(fn);
		m_fns.insert(fn);
	}

	m_error = Error::NO_ERROR;
	return true;
}

std::string CCalculator::GetAllVarsVales()
{
	std::string result;
	std::ostringstream strs;
	strs << std::setprecision(3);

	for (const auto& [name, val] : m_vars)
	{
		strs << name << ": ";
		if (val->HaveValue())
		{
			strs << val->GetValue();
		}
		else
		{
			strs << "nan";
		}
		strs << std::endl;
	}

	result = strs.str();
	return result;
}

std::string CCalculator::GetAllFnsVales()
{
	std::string result;
	std::ostringstream strs;
	strs << std::setprecision(3);

	for (const auto& [name, fn] : m_fns)
	{
		strs << name << ": ";
		if (fn->HaveValue())
		{
			strs << fn->GetValue();
		}
		else
		{
			strs << "nan";
		}
		strs << std::endl;
	}

	result = strs.str();
	return result;
}

COperator CCalculator::GetMathOperator(std::string str) const
{
	if (str == "+")
		return COperator::Addition;
	if (str == "-")
		return COperator::Subtraction;
	if (str == "*")
		return COperator::Multiplication;
	if (str == "/")
		return COperator::Division;
	return COperator::Undefined;
}

Error CCalculator::GetError() const
{
	return m_error;
}
