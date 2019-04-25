#include "stdafx.h"
#include "calculator.h"
#include "Variable.h"
#include "Function.h"

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
	auto it = m_vars.find(identifier);

	std::pair<std::string, std::shared_ptr<CVariable>> var;

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
	try
	{
		value = std::stod(valueStr);
	}
	catch (const std::exception&)
	{
		m_error = Error::VALUE_INCORRECT;
		return false;
	}

	var.second->SetValue(value);

	return true;
}

bool CCalculator::GetValue(const std::string& identifier, std::string& result)
{
	/*auto it = m_names.find(identifier);

	if (it != m_names.end())
	{
	}*/
	
	auto it = m_vars.find(identifier);
	if (it != m_vars.end())
	{
		auto var = *it->second;
		if (var.HaveValue())
		{		 
			double value = var.GetValue();
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

	return result;
}

Error CCalculator::GetError() const
{
	return m_error;
}
