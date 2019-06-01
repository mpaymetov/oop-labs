#pragma once

#include "stdafx.h"
#include "UserInterface.h"
#include "calculator.h"
#include "operator.h"

COperator GetMathOperator(std::string str)
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

CUserInterface::CUserInterface(CCalculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "var", std::bind(&CUserInterface::Var, this, std::placeholders::_1) },
		  { "let", std::bind(&CUserInterface::Let, this, std::placeholders::_1) },
		  { "fn", std::bind(&CUserInterface::Fn, this, std::placeholders::_1) },
		  { "print", std::bind(&CUserInterface::Print, this, std::placeholders::_1) },
		  { "printvars", std::bind(&CUserInterface::Printvars, this, std::placeholders::_1) },
		  { "printfns", std::bind(&CUserInterface::Printfns, this, std::placeholders::_1) } })
{
}

bool CUserInterface::ExecuteCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CUserInterface::Var(std::istream& args)
{
	std::string identifier;
	std::string errorMsg;
	args >> identifier;
	if (!m_calculator.SetVar(identifier, errorMsg))
	{
		m_output << errorMsg << std::endl;
	}
	return true;
}

bool CUserInterface::Let(std::istream& args)
{
	std::string identifier, assign, valueStr, errorMsg;
	args >> identifier >> assign >> valueStr;

	if (assign != "=")
	{
		m_output << "do not find '='" << std::endl;
		return true;
	}

	if (valueStr.empty())
	{
		m_output << "value string is empty" << std::endl;
		return true;
	}

	double value;
	try
	{
		value = std::stod(valueStr);
	}
	catch (const std::exception&)
	{
		if (!m_calculator.GetValue(valueStr, value, errorMsg))
		{
			m_output << errorMsg << std::endl;
			return true;
		}		
	}

	if (!m_calculator.SetValue(identifier, value, errorMsg))
	{
		m_output << errorMsg << std::endl;
	}
	return true;
}

bool CUserInterface::Fn(std::istream& args)
{
	std::string identifier, assign, firstOperand, mathOperatorStr, secondOperand, errorMsg;
	args >> identifier >> assign >> firstOperand >> mathOperatorStr >> secondOperand;

	if (assign != "=")
	{
		m_output << "do not find '='" << std::endl;
		return true;
	}

	COperator mathOperator = GetMathOperator(mathOperatorStr);

	if (!m_calculator.SetFn(identifier, firstOperand, mathOperator, secondOperand, errorMsg))
	{
		m_output << errorMsg << std::endl;
	}

	return true;
}

bool CUserInterface::Print(std::istream& args)
{
	std::string identifier, errorMsg;
	double result;
	args >> identifier;
	if (m_calculator.GetValue(identifier, result, errorMsg))
	{
		m_output << result << std::endl;
	}
	else
	{
		m_output << errorMsg << std::endl;
	}
	return true;
}

bool CUserInterface::Printvars(std::istream& args)
{
	std::map<std::string, double> vars = m_calculator.GetAllVarsVales();
	for (const auto& [name, val] : vars)
	{
		m_output << name << ": " << std::setprecision(3) << val << std::endl;
	}
	return true;
}

bool CUserInterface::Printfns(std::istream& args)
{
	std::map<std::string, double> fns = m_calculator.GetAllFnsVales();
	for (const auto& [name, val] : fns)
	{
		m_output << name << ": " << std::setprecision(3) << val << std::endl;
	}
	return true;
}
